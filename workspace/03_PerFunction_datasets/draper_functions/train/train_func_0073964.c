config_load_from_file (Configuration *config, const gchar *path, GError **error)
{
    GKeyFile *key_file;
    gchar **groups;
    int i;

    key_file = g_key_file_new ();
    if (!g_key_file_load_from_file (key_file, path, G_KEY_FILE_NONE, error))
    {
        g_key_file_free (key_file);
        return FALSE;
    }

    groups = g_key_file_get_groups (key_file, NULL);
    for (i = 0; groups[i]; i++)
    {
        gchar **keys;
        int j;

        keys = g_key_file_get_keys (key_file, groups[i], NULL, error);
        if (!keys)
            break;

        for (j = 0; keys[j]; j++)
        {
            gchar *value;

            value = g_key_file_get_value (key_file, groups[i], keys[j], NULL);
            g_key_file_set_value (config->priv->key_file, groups[i], keys[j], value);
            g_free (value);
        }

        g_strfreev (keys);
    }
    g_strfreev (groups);

    g_key_file_free (key_file);

    return TRUE;
}
