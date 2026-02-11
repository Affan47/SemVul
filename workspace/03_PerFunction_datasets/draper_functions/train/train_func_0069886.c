radio_conf_save (radio_conf_t *conf)
{
    GKeyFile *cfg = NULL;
    gchar    *confdir;
    gchar    *fname;
    gchar    *data;
    gsize     len;

    if (conf->name == NULL) {
        sat_log_log (SAT_LOG_LEVEL_ERROR,
                     _("%s: NULL configuration name!"),
                     __FUNCTION__);
        return;
    }


    cfg = g_key_file_new();

    g_key_file_set_string (cfg, GROUP, KEY_HOST, conf->host);
    g_key_file_set_integer (cfg, GROUP, KEY_PORT, conf->port);
    g_key_file_set_double (cfg, GROUP, KEY_LO, conf->lo);
    g_key_file_set_double (cfg, GROUP, KEY_LOUP, conf->loup);
    g_key_file_set_integer (cfg, GROUP, KEY_TYPE, conf->type);
    g_key_file_set_integer (cfg, GROUP, KEY_PTT, conf->ptt);

    if (conf->type == RIG_TYPE_DUPLEX) {
        g_key_file_set_integer (cfg, GROUP, KEY_VFO_UP, conf->vfoUp);
        g_key_file_set_integer (cfg, GROUP, KEY_VFO_DOWN, conf->vfoDown);
    }


    data = g_key_file_to_data (cfg, &len, NULL);

    confdir = get_hwconf_dir();
    fname = g_strconcat (confdir, G_DIR_SEPARATOR_S,
                         conf->name, ".rig", NULL);
    g_free (confdir);

    g_file_set_contents (fname, data, len, NULL);

    g_free (fname);
    g_free (data);
    g_key_file_free (cfg);

    sat_log_log (SAT_LOG_LEVEL_MSG,
                 _("%s: Saved radio configuration %s"),
                 __FUNCTION__, conf->name);
}
