get_estimated_delay(BEST_APP_VERSION& bav) {
    int pt = bav.host_usage.proc_type;
    if (pt == PROC_TYPE_CPU) {
        return g_request->cpu_estimated_delay;
    }
    COPROC* cp = g_request->coprocs.type_to_coproc(pt);
    return cp->estimated_delay;
}
