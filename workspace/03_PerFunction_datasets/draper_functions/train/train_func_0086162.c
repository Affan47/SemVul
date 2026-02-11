CachedDiskUsageUpdate() {
    bool immediate = false;

    if (! IsConnected()) return -1;


#if USE_CACHE_TIMEOUTS
    wxTimeSpan ts(wxDateTime::Now() - m_dtDiskUsageTimestamp);
    if (ts.GetSeconds() >= (2 * DISKUSAGERPC_INTERVAL)) immediate = true;
#endif
    if (disk_usage.projects.empty()) immediate = true;
    if (m_dtDiskUsageTimestamp.IsEqualTo(wxDateTime((time_t)0))) immediate = true;

    if (immediate) {
        m_dtDiskUsageTimestamp = wxDateTime::Now();
        m_iGet_dsk_usage_rpc_result = rpc.get_disk_usage(disk_usage);
    }

    if (m_iGet_dsk_usage_rpc_result) {
        wxLogTrace(wxT("Function Status"), wxT("Get Disk Usage Failed '%d'"), m_iGet_dsk_usage_rpc_result);
        ForceCacheUpdate();
    }

    return m_iGet_dsk_usage_rpc_result;
}
