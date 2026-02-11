handle_set_gpu_mode(GUI_RPC_CONN& grc) {
    double duration = 0;
    bool btemp;
    int mode=-1;
    while (!grc.xp.get_tag()) {
        if (grc.xp.parse_double("duration", duration)) continue;
        if (grc.xp.parse_bool("always", btemp)) {
            mode = RUN_MODE_ALWAYS;
            continue;
        }
        if (grc.xp.parse_bool("never", btemp)) {
            mode = RUN_MODE_NEVER;
            continue;
        }
        if (grc.xp.parse_bool("auto", btemp)) {
            mode = RUN_MODE_AUTO;
            continue;
        }
        if (grc.xp.parse_bool("restore", btemp)) {
            mode = RUN_MODE_RESTORE;
            continue;
        }
    }
    if (mode < 0) {
        grc.mfout.printf("<error>Missing mode</error>\n");
        return;
    }
    gstate.gpu_run_mode.set(mode, duration);
    gstate.request_schedule_cpus("GPU mode changed");
    grc.mfout.printf("<success/>\n");
}
