gnc_history_update_menus (GncMainWindow *window)
{
    gchar *filename, *pref;
    guint i;

    ENTER("");
    for (i = 0; i < MAX_HISTORY_FILES; i++)
    {
        pref = gnc_history_index_to_pref_name(i);
        filename = gnc_prefs_get_string(GNC_PREFS_GROUP_HISTORY, pref);
        gnc_history_update_action(window, i, filename);
        g_free(filename);
        g_free(pref);
    }
    LEAVE("");
}
