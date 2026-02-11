mod_mgr_save_state ()
{
    guint      num;
    guint      i;
    GtkWidget *module;
    gchar     *mods = NULL;
    gchar     *buff;


    if (!nbook) {
        sat_log_log (SAT_LOG_LEVEL_BUG,
                     _("%s: Attempt to save state but mod-mgr is NULL?"),
                     __FUNCTION__);
        return;
    }

    num = g_slist_length (modules);

    if (num == 0) {
        sat_log_log (SAT_LOG_LEVEL_MSG,
                     _("%s: No modules need to save state."),
                     __FUNCTION__);

        sat_cfg_set_str (SAT_CFG_STR_OPEN_MODULES, NULL);

        return;
    }

    for (i = 0; i < num; i++) {
        module = GTK_WIDGET (g_slist_nth_data (modules, i));


        mod_cfg_save (GTK_SAT_MODULE (module)->name, GTK_SAT_MODULE (module)->cfgdata);

        if (i == 0) {
            buff = g_strdup (GTK_SAT_MODULE (module)->name);
        }
        else {
            buff = g_strconcat (mods, ";", GTK_SAT_MODULE (module)->name, NULL);
            g_free (mods);
        }

        mods = g_strdup (buff);
        g_free (buff);

        sat_log_log (SAT_LOG_LEVEL_DEBUG, _("%s: Stored %s"),
                     __FUNCTION__, GTK_SAT_MODULE (module)->name);

    }

    sat_log_log (SAT_LOG_LEVEL_MSG, _("%s: Saved states for %d modules."),
                 __FUNCTION__, num);

    sat_cfg_set_str (SAT_CFG_STR_OPEN_MODULES, mods);

    g_free (mods);
}
