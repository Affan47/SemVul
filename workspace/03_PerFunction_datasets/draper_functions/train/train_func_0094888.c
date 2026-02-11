_iq_version_free(module_t mod) {
    mod_iq_version_config_t config = (mod_iq_version_config_t) mod->private;

    sm_unregister_ns(mod->mm->sm, uri_VERSION);
    feature_unregister(mod->mm->sm, uri_VERSION);

    if(config->os_name != NULL) free(config->os_name);
    if(config->os_release != NULL) free(config->os_release);

    free(config);
}
