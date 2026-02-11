requesting_work() {
    if (g_request->work_req_seconds > 0) return true;
    if (g_request->cpu_req_secs > 0) return true;
    if (g_request->coprocs.nvidia.count && g_request->coprocs.nvidia.req_secs) return true;
    if (g_request->coprocs.ati.count && g_request->coprocs.ati.req_secs) return true;
    if (g_request->coprocs.intel_gpu.count && g_request->coprocs.intel_gpu.req_secs) return true;
    if (ssp->have_nci_app) return true;
    return false;
}
