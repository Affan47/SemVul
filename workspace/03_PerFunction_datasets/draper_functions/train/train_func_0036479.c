OnUpdateUI(wxUpdateUIEvent& )

{
    wxMenuBar* pbar = Manager::Get()->GetAppFrame()->GetMenuBar();

    #if defined(LOGGING)
    LOGIT( _T("OnUpdateUI Window[%p],Pid[%d]"), GetSnippetsWindow(), m_ExternalPid );
    #endif


    if (not GetSnippetsWindow() && (not m_ExternalPid) )
    {   pbar->Check(idViewSnippets, false);
        #if defined(LOGGING)
        LOGIT( _T("OnUpdateUI Check[%s]"), wxT("to OFF") );
        #endif
         return;
    }

    if ( (not GetSnippetsWindow()) && m_ExternalPid )
    {
        if (not ::wxProcess::Exists(m_ExternalPid))
        {
            RemoveKeepAliveFile();
            m_ExternalPid = 0;
        }
        pbar->Check(idViewSnippets, m_ExternalPid);
        return;
    }


	if (GetSnippetsWindow() )
    {    pbar->Check(idViewSnippets, IsWindowReallyShown(GetSnippetsWindow()));
        return;
    }


    if (m_ExternalPid)
    {
        pbar->Check(idViewSnippets, m_ExternalPid!=0);

    }

}
