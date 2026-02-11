OnDialogDone(cbDragScrollCfg* pDlg)

{


    MouseDragScrollEnabled  = pDlg->GetMouseDragScrollEnabled();
    MouseEditorFocusEnabled = pDlg->GetMouseEditorFocusEnabled();
    MouseFocusEnabled       = pDlg->GetMouseFocusEnabled();
    MouseDragDirection      = pDlg->GetMouseDragDirection();
    MouseDragKey            = pDlg->GetMouseDragKey();
    MouseDragSensitivity    = pDlg->GetMouseDragSensitivity();
    MouseToLineRatio        = pDlg->GetMouseToLineRatio();
    MouseContextDelay       = pDlg->GetMouseContextDelay();
    MouseWheelZoom          = pDlg->GetMouseWheelZoom();
    PropagateLogZoomSize    = pDlg->IsLogZoomSizePropagated() and MouseWheelZoom;
    #ifdef LOGGING
     LOGIT(_T("MouseDragScrollEnabled:%d"),  MouseDragScrollEnabled);
     LOGIT(_T("MouseEditorFocusEnabled:%d"), MouseEditorFocusEnabled);
     LOGIT(_T("MouseFocusEnabled:%d"),       MouseFocusEnabled);
     LOGIT(_T("MouseDragDirection:%d"),      MouseDragDirection);
     LOGIT(_T("MouseDragKey:%d"),            MouseDragKey);
     LOGIT(_T("MouseDragSensitivity:%d"),    MouseDragSensitivity);
     LOGIT(_T("MouseToLineRatio:%d"),        MouseToLineRatio);
     LOGIT(_T("MouseContextDelay:%d"),       MouseContextDelay);
     LOGIT(_T("MouseMouseWheelZoom:%d"),     MouseWheelZoom);
     LOGIT(_T("PropagateLogZoomSize:%d"),    PropagateLogZoomSize);
     LOGIT(_T("-----------------------------"));
    #endif


    wxUpdateUIEvent eventdone(ID_DLG_DONE);
    eventdone.SetEventObject( m_pCB_AppWindow );
    m_pCB_AppWindow->GetEventHandler()->AddPendingEvent(eventdone);


}
