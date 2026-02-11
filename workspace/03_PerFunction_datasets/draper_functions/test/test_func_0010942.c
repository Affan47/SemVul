scale_versions(APP &app, double avg, SCHED_SHMEM *ssp) {
    char buf[256];
    int retval;

    for (int j=0; j<ssp->napp_versions; j++) {
        APP_VERSION &av = ssp->app_versions[j];
        if (av.appid != app.id) {
            continue;
        }
        if (av.pfc.n < MIN_VERSION_SAMPLES) {
            continue;
        }
        av.pfc_scale= avg/av.pfc.get_avg();

        DB_APP_VERSION dav;
        dav.id = av.id;
        sprintf(buf, "pfc_scale=%.15e", av.pfc_scale);
        retval = dav.update_field(buf);
        if (retval) {
            return retval;
        }
        if (config.debug_credit) {
            PLATFORM *p = ssp->lookup_platform_id(av.platformid);
            log_messages.printf(MSG_NORMAL,
                " updating scale factor for %d (%s %s)\n",
                av.id, p->name, av.plan_class
            );
            log_messages.printf(MSG_NORMAL,
                "  n: %g avg PFC: %g new scale: %g\n",
                av.pfc.n, av.pfc.get_avg(), av.pfc_scale
            );
        }
    }
    app.min_avg_pfc = avg;
    DB_APP da;
    da.id = app.id;
    sprintf(buf, "min_avg_pfc=%.15e", avg);
    retval = da.update_field(buf);
    if (retval) {
        return retval;
    }
    return 0;
}
