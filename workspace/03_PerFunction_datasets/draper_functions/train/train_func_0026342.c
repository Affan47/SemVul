OnMnuSearchExtended(wxCommandEvent& event)

{
    wxWindow* m_pAppWindow = Manager::Get()->GetAppWindow();
    if ( not m_pAppWindow ) m_pAppWindow = wxTheApp->GetTopWindow();


    if ( GetFileChanged() ){
        GetSnippetsTreeCtrl()->SaveItemsToFile( GetConfig()->SettingsSnippetsXmlPath );
        #if defined(LOGGING)
        LOGIT( _T("OnMnuSearchExtended Saved[%s]"), GetConfig()->SettingsSnippetsXmlPath.c_str());
        #endif
    }


    wxWindow* pThreadSearchFrame = GetConfig()->GetThreadSearchFrame();
    if ( pThreadSearchFrame )
    {
        pThreadSearchFrame->Raise();
        pThreadSearchFrame->SetFocus();
    }
    else
    {
        pThreadSearchFrame = new ThreadSearchFrame((wxFrame*)m_pAppWindow, _T("Snippets Search"));
        GetConfig()->SetThreadSearchFrame( pThreadSearchFrame );
    }

    if (pThreadSearchFrame)
    {
        pThreadSearchFrame->Show();

        CodeSnippetsEvent evt( wxEVT_CODESNIPPETS_NEW_INDEX, 0);
        evt.SetSnippetString( GetConfig()->SettingsSnippetsXmlPath );
        evt.PostCodeSnippetsEvent(evt);


        if ( wxEvtHandler* pds = GetConfig()->GetDragScrollEvtHandler())
        {
            sDragScrollEvent dsevt(wxEVT_S_DRAGSCROLL_EVENT,idDragScrollRescan);
            dsevt.SetEventObject( pThreadSearchFrame );
            dsevt.SetString(wxEmptyString);
            pds->AddPendingEvent(dsevt);
        }

    }

}
