CachedSimpleGUIUpdate(bool bForce) {
    int     i = 0;

    if (! IsConnected()) return -1;

#if USE_CACHE_TIMEOUTS
    wxTimeSpan ts(wxDateTime::Now() - m_dtCachedSimpleGUITimestamp);
    if (ts.GetSeconds() >= (2 * CACHEDSIMPLEGUIRPC_INTERVAL)) bForce = true;
#endif
    if (m_dtCachedSimpleGUITimestamp.IsEqualTo(wxDateTime((time_t)0))) bForce = true;
    if (bForce) {
        m_dtCachedSimpleGUITimestamp = wxDateTime::Now();
        m_iGet_simple_gui2_rpc_result = rpc.get_simple_gui_info(async_projects_update_buf, state, results);
    }

    if (m_iGet_simple_gui2_rpc_result) {
        wxLogTrace(wxT("Function Status"), wxT("CMainDocument::CachedSimpleGUIUpdate - Get Simple GUI Failed '%d'"), m_iGet_simple_gui2_rpc_result);
        ForceCacheUpdate();
    }

    m_fProjectTotalResourceShare = 0.0;
    for (i=0; i < (long)state.projects.size(); i++) {
        m_fProjectTotalResourceShare += state.projects.at(i)->resource_share;
    }
    if (!m_fProjectTotalResourceShare) m_fProjectTotalResourceShare = 1;

    return m_iGet_simple_gui2_rpc_result;
}
