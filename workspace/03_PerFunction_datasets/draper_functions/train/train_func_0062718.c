Notify()

{


    if ( !IsAttached() )
        return;


    m_pThreadSearchView->Clear();

    m_pThreadSearchView->Update();
    SaveConfig(m_pViewManager->IsViewShown(),
               m_pThreadSearchView->GetSashPosition(),
               m_pViewManager->GetManagerType(),
               m_pThreadSearchView->GetSearchHistory());


    if ( m_FindData.MustSearchInProject() == true )
    {

        CodeSnippetsEvent evt(wxEVT_CODESNIPPETS_GETFILELINKS, 0);

        evt.ProcessCodeSnippetsEvent(evt);
    }
    else
        GetConfig()->GetFileLinksMapArray().clear();
}
