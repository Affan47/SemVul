ResetNotebookSashPosition()

{
    if (m_pMainPanel && m_pMainPanel->m_pSplitterWindow && m_pThreadSearchView && m_pEdNotebook)
    if ( m_pMainPanel->m_pSplitterWindow->IsSplit())
    {


        if (m_EdNotebookSashPosition)
            m_pMainPanel->m_pSplitterWindow->SetSashPosition( m_EdNotebookSashPosition );
    }
}
