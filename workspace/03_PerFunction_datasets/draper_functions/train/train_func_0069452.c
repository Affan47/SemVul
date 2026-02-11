submit_host_info(struct optstruct *opts)
{
    struct cl_engine *engine;
    cli_intel_t *intel;

    if (!optget(opts, "enable-stats")->enabled)
        return;

    engine = cl_engine_new();
    if (!(engine))
        return;

    if (optget (opts, "Debug")->enabled || optget (opts, "debug")->enabled)
        cl_debug ();

    if (optget (opts, "verbose")->enabled)
        mprintf_verbose = 1;

    cl_engine_stats_enable(engine);

    intel = engine->stats_data;
    if (!(intel)) {
        engine->cb_stats_submit = NULL;
        cl_engine_free(engine);
        return;
    }

    intel->host_info = calloc(1, strlen(TARGET_OS_TYPE) + strlen(TARGET_ARCH_TYPE) + 2);
    if (!(intel->host_info)) {
        engine->cb_stats_submit = NULL;
        cl_engine_free(engine);
        return;
    }

    sprintf(intel->host_info, "%s %s", TARGET_OS_TYPE, TARGET_ARCH_TYPE);

    if (!strcmp(hostid, "none"))
        cl_engine_set_clcb_stats_get_hostid(engine, NULL);
    else if (strcmp(hostid, "default"))
        cl_engine_set_clcb_stats_get_hostid(engine, get_hostid);

    if (optget(opts, "stats-timeout")->enabled) {
        cl_engine_set_num(engine, CL_ENGINE_STATS_TIMEOUT, optget(opts, "StatsTimeout")->numarg);
    }

    cl_engine_free(engine);
}
