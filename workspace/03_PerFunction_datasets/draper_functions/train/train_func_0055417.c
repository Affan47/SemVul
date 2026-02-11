qof_log_parse_log_config(const char *filename)
{
    const gchar *levels_group = "levels", *output_group = "output";
    GError *err = NULL;
    GKeyFile *conf = g_key_file_new();

    if (!g_key_file_load_from_file(conf, filename, G_KEY_FILE_NONE, &err))
    {
        g_warning("unable to parse [%s]: %s", filename, err->message);
        g_error_free(err);
        return;
    }

    g_debug("parsing log config from [%s]", filename);
    if (g_key_file_has_group(conf, levels_group))
    {
        gsize num_levels;
        int key_idx;
        gchar **levels;

        levels = g_key_file_get_keys(conf, levels_group, &num_levels, NULL);

        for (key_idx = 0; key_idx < num_levels && levels[key_idx] != NULL; key_idx++)
        {
            QofLogLevel level;
            gchar *logger_name = NULL, *level_str = NULL;

            logger_name = g_strdup(levels[key_idx]);
            level_str = g_key_file_get_string(conf, levels_group, logger_name, NULL);
            level = qof_log_level_from_string(level_str);

            g_debug("setting log [%s] to level [%s=%d]", logger_name, level_str, level);
            qof_log_set_level(logger_name, level);

            g_free(logger_name);
            g_free(level_str);
        }
        g_strfreev(levels);
    }

    if (g_key_file_has_group(conf, output_group))
    {
        gsize num_outputs;
        int output_idx;
        gchar **outputs;

        outputs = g_key_file_get_keys(conf, output_group, &num_outputs, NULL);
        for (output_idx = 0; output_idx < num_outputs && outputs[output_idx] != NULL; output_idx++)
        {
            gchar *key = outputs[output_idx];
            gchar *value;

            if (g_ascii_strcasecmp("to", key) != 0)
            {
                g_warning("unknown key [%s] in [outputs], skipping", key);
                continue;
            }

            value = g_key_file_get_string(conf, output_group, key, NULL);
            g_debug("setting [output].to=[%s]", value);
            qof_log_init_filename_special(value);
            g_free(value);
        }
        g_strfreev(outputs);
    }

    g_key_file_free(conf);
}
