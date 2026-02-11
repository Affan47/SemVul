OnSizeWindow(wxSizeEvent &event)

{


    #if defined(LOGGING)
    LOGIT( _T("ThreadSearchFrame::OnSizeWindow"));
    #endif

    event.Skip();
    if (not GetConfig()->GetThreadSearchPlugin() ) return;
    GetConfig()->GetThreadSearchPlugin()->UserResizingWindow(event);
    event.Skip();
    return;
}
