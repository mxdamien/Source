//
// CWindow.cpp
//

#ifdef _WIN32
#define STRICT
#include <windows.h>
#include <stdio.h>
#include "CFile.h"
#include "CWindow.h"

///////////////////////
// -CDialogBase

BOOL CALLBACK CDialogBase::DialogProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) // static
{
	CDialogBase * pDlg;
	if ( message == WM_INITDIALOG )
	{
		pDlg = (CDialogBase *)( lParam );
		pDlg->m_hWnd = hWnd;	// OnCreate()
		pDlg->SetWindowLong( GWL_USERDATA, (DWORD) pDlg );
	}
	else
	{
		pDlg = (CDialogBase *)(LPVOID)::GetWindowLong( hWnd, GWL_USERDATA );
	}
	if ( pDlg )
	{
		return pDlg->DefDialogProc( message, wParam, lParam );
	}
	else
	{
		return FALSE;
	}
}

///////////////////////
// -CWindowBase

LRESULT WINAPI CWindowBase::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) // static
{
	// NOTE: It is important to call OnDestroy() for asserts to work.
	CWindowBase * pWnd;
	if ( message == WM_NCCREATE || message == WM_CREATE )
	{
		LPCREATESTRUCT lpCreateStruct = (LPCREATESTRUCT)lParam;
		CWindowBase *pWnd = (CWindowBase *)(lpCreateStruct->lpCreateParams);
		pWnd->m_hWnd = hWnd;	// OnCreate()
		pWnd->SetWindowLong(GWL_USERDATA, (DWORD)pWnd);
	}
	pWnd = (CWindowBase *)(LPVOID)::GetWindowLong( hWnd, GWL_USERDATA );
	return ( pWnd ? pWnd->DefWindowProc(message, wParam, lParam) : ::DefWindowProc(hWnd, message, wParam, lParam) );
}

#endif // _WIN32
