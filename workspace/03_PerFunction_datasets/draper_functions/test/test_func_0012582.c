capped_host_fpops() {
    double x = g_request->host.p_fpops;
    if (!ssp) return x;
    if (x <= 0) {
        return ssp->perf_info.host_fpops_50_percentile;
    }
    if (x > ssp->perf_info.host_fpops_95_percentile*1.1) {
        return ssp->perf_info.host_fpops_95_percentile*1.1;
    }
    return x;
}
