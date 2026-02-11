plugin_load_dir(const gchar * path)
{
    GDir *dir = g_dir_open(path, 0, NULL);
    int failure = 0;
    if (dir)
    {
        const gchar *dirname = NULL;
        while ((dirname = g_dir_read_name(dir)) != NULL)
        {
            gchar *full_path =
                g_strdup_printf("%s%c%s", path, G_DIR_SEPARATOR, dirname);

            if (g_str_has_suffix(dirname, G_MODULE_SUFFIX))
            {
                GError *error = NULL;
                if (plugin_load(path, dirname, &error))
                {
                    failure = 1;
                    playlist3_show_error_message(error->message,
                                                 ERROR_CRITICAL);
                    g_log(PLUGIN_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL,
                          "Failed to load plugin: %s: %s\n", dirname,
                          error->message);
                    g_error_free(error);
                    error = NULL;
                }
            } else
            {
                g_log(PLUGIN_LOG_DOMAIN, G_LOG_LEVEL_INFO,
                      "%s not loaded, wrong extension, should be: '%s'",
                      dirname, G_MODULE_SUFFIX);
            }
            q_free(full_path);
        }
        g_dir_close(dir);
    }
    if (failure)
    {
        gtk_init_add(__show_plugin_load_error, NULL);
    }
}
