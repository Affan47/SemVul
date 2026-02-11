confirm_current_assignment(
    RESULT* rp, double usage, COPROC* cp
) {
    double x = (usage<1)?usage:1;
    for (int i=0; i<usage; i++) {
        int j = rp->coproc_indices[i];
        cp->usage[j] +=x;
        cp->pending_usage[j] -=x;
        if (log_flags.coproc_debug) {
            msg_printf(rp->project, MSG_INFO,
                "[coproc] %s instance %d: confirming %f instance for %s",
                cp->type, j, x, rp->name
            );
        }
#if DEFER_ON_GPU_AVAIL_RAM
        cp->available_ram_temp[j] -= rp->avp->gpu_ram;
#endif
    }
}
