module_init(mod_instance_t mi, char *arg) {
    module_t mod = mi->mod;
    mod_amp_config_t config;
    char* option;

    if (mod->init) return 0;

    config = (mod_amp_config_t) calloc(1, sizeof(struct _mod_amp_config_st));

    config->sm = mod->mm->sm;
    option = config_get_one(mod->mm->sm->config, "amp.disableactions.drop", 0);
    if (option != NULL) {
        log_debug(ZONE, "action Drop disabled in config.");
        config->disableActionDrop = 1;
    }
    option = config_get_one(mod->mm->sm->config, "amp.disableactions.error", 0);
    if (option != NULL) {
        log_debug(ZONE, "action Error disabled in config.");
        config->disableActionError = 1;
    }
    option = config_get_one(mod->mm->sm->config, "amp.disableactions.alert", 0);
    if (option != NULL) {
        log_debug(ZONE, "action Alert disabled in config.");
        config->disableActionAlert = 1;
    }
    option = config_get_one(mod->mm->sm->config, "amp.disableactions.notify", 0);
    if (option != NULL) {
        log_debug(ZONE, "action Notify disabled in config.");
        config->disableActionNotify = 1;
    }
    option = config_get_one(mod->mm->sm->config, "amp.disableconditions.deliver", 0);
    if (option != NULL) {
        log_debug(ZONE, "condition Deliver disabled in config.");
        config->disableConditionDeliver = 1;
    }
    option = config_get_one(mod->mm->sm->config, "amp.disableconditions.expireat", 0);
    if (option != NULL) {
        log_debug(ZONE, "condition Expire-At disabled in config.");
        config->disableConditionExpireAt = 1;
    }
    option = config_get_one(mod->mm->sm->config, "amp.disableconditions.matchresource", 0);
    if (option != NULL) {
        log_debug(ZONE, "condition Match-Resource disabled in config.");
        config->disableConditionMatchResource = 1;
    }
    option = config_get_one(mod->mm->sm->config, "amp.offlinestoragedisabled", 0);
    if (option != NULL) {
        log_debug(ZONE, "offline storage disabled in config.");
        config->offlinestorageDisabled = 1;
    }
    option = config_get_one(mod->mm->sm->config, "offline.dropmessages", 0);
    if (option != NULL) {
        log_debug(ZONE, "offline storage disabled in config.");
        config->offlinestorageDisabled = 1;
    }

    mod->private = config;

    mod->in_sess = _amp_in_sess;
    mod->pkt_user = _amp_pkt_user;
    mod->pkt_sm = _amp_pkt_sm;
    mod->free = _amp_free;

    feature_register(mod->mm->sm, uri_AMP);

    return 0;
}
