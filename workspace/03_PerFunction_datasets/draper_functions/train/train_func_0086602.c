cpu_benchmarks_set_defaults() {
    if (!host_info.p_fpops) host_info.p_fpops = DEFAULT_FPOPS;
    if (!host_info.p_iops) host_info.p_iops = DEFAULT_IOPS;
    if (!host_info.p_membw) host_info.p_membw = DEFAULT_MEMBW;
    if (!host_info.m_cache) host_info.m_cache = DEFAULT_CACHE;
}
