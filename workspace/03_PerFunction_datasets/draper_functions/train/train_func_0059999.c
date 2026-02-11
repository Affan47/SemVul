host_path_data_set_language (HostPathData *data, const char *language)
{
        char *old_language = data->default_language;

        if ((old_language != NULL) && (!strcmp (language, old_language)))
                return;

        data->default_language = g_strdup (language);


        if (old_language != NULL)
                g_free (old_language);
}
