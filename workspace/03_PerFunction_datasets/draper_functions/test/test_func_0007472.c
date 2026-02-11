fm_config_finalize(GObject *object)
{
    FmConfig* cfg;
    g_return_if_fail(object != NULL);
    g_return_if_fail(FM_IS_CONFIG(object));

    cfg = (FmConfig*)object;
    _cfg_monitor_free(cfg);
    g_free(cfg->_cfg_name);
    if(cfg->terminal)
        g_free(cfg->terminal);
    if(cfg->archiver)
        g_free(cfg->archiver);
    g_strfreev(cfg->system_modules_blacklist);
    g_strfreev(cfg->modules_blacklist);
    g_strfreev(cfg->modules_whitelist);
    g_free(cfg->format_cmd);
    g_free(cfg->list_view_size_units);
    g_free(cfg->saved_search);

    G_OBJECT_CLASS(fm_config_parent_class)->finalize(object);
}
