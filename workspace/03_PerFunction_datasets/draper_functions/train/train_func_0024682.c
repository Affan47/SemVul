file_retain_type_changed_cb(gpointer gsettings, gchar *key, gpointer user_data)
{
    XMLFileRetentionType type = XML_RETAIN_ALL;

    if (gnc_prefs_is_set_up())
    {
        if (gnc_prefs_get_bool (GNC_PREFS_GROUP_GENERAL, GNC_PREF_RETAIN_TYPE_NEVER))
            type = XML_RETAIN_NONE;
        else if (gnc_prefs_get_bool (GNC_PREFS_GROUP_GENERAL, GNC_PREF_RETAIN_TYPE_DAYS))
            type = XML_RETAIN_DAYS;
        else if (!gnc_prefs_get_bool (GNC_PREFS_GROUP_GENERAL, GNC_PREF_RETAIN_TYPE_FOREVER))
            PWARN("no file retention policy was set, assuming conservative policy 'forever'");

        gnc_prefs_set_file_retention_policy (type);
    }
}
