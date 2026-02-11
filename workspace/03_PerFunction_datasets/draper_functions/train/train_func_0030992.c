UnsplitThreadSearchWindow()

{
    if (m_pMainPanel && m_pMainPanel->m_pSplitterWindow && m_pThreadSearchView && m_pEdNotebook)
    if ( m_pMainPanel->m_pSplitterWindow->IsSplit())
    {

        m_EdNotebookSashPosition = m_pMainPanel->m_pSplitterWindow->GetSashPosition();
        ConfigManager* pCfg = Manager::Get()->GetConfigManager(_T("SnippetsSearch"));
        pCfg->Write( wxT("/EdNotebookSashPosn"), m_EdNotebookSashPosition);
        m_pMainPanel->m_pSplitterWindow->Unsplit();
    }
}
