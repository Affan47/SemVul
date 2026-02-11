theft_run(struct theft *t, struct theft_cfg *cfg) {
    if (t == NULL | cfg == NULL) {
        return THEFT_RUN_ERROR_BAD_ARGS;
    }

    struct theft_propfun_info info;
    memset(&info, 0, sizeof(info));
    info.name = cfg->name;
    info.fun = cfg->fun;
    memcpy(info.type_info, cfg->type_info, sizeof(info.type_info));
    info.always_seed_count = cfg->always_seed_count;
    info.always_seeds = cfg->always_seeds;

    if (cfg->seed) { theft_set_seed(t, cfg->seed); }

    if (cfg->trials == 0) { cfg->trials = THEFT_DEF_TRIALS; }

    return theft_run_internal(t, &info, cfg->trials, cfg->progress_cb,
        cfg->env, cfg->report);
}
