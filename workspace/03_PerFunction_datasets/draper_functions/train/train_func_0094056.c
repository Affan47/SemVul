filename_from_display (const gchar *string)
{
    GError *error = NULL;
    gchar *ret = NULL;
    const gchar *char_encoding = NULL;


    g_return_val_if_fail (string != NULL, NULL);


    if (get_locale())
        char_encoding = strchr(get_locale(), '.');

    if (char_encoding)
        char_encoding = char_encoding+1;
    if (char_encoding)
    {
        error = NULL;

        if (FILENAME_CHARACTER_SET_OTHER)
        {
            ret = g_convert(string, -1, char_encoding, "UTF-8", NULL, NULL, &error);

        }else if (FILENAME_CHARACTER_SET_APPROXIMATE)
        {


            gchar *enc = g_strconcat(char_encoding, "//TRANSLIT", NULL);
            ret = g_convert(string, -1, enc, "UTF-8", NULL, NULL, &error);
            g_free(enc);

        }else if (FILENAME_CHARACTER_SET_DISCARD)
        {


            gchar *enc = g_strconcat(char_encoding, "//IGNORE", NULL);
            ret = g_convert(string, -1, enc, "UTF-8", NULL, NULL, &error);
            g_free(enc);
        }
    }

    if (!ret)
    {

        char_encoding = get_encoding_from_locale(get_locale());
        if (char_encoding)
        {

            error = NULL;
            ret = g_convert(string, -1, char_encoding, "UTF-8", NULL, NULL, &error);
        }
    }

    if (!ret)
    {

        error = NULL;
        ret = g_convert(string, -1, "ISO-8859-1", "UTF-8", NULL, NULL, &error);
    }

    if (!ret)
    {
        if (g_utf8_validate(string, -1, NULL))
        {

            ret = g_strdup(string);
        }
    }

    if (!ret)
    {

        gchar *escaped_str = g_strescape(string, NULL);
        Log_Print(LOG_ERROR,_("The UTF-8 string '%s' couldn't be converted into filename encoding (%s)."),
                    escaped_str, error && error->message ? error->message : _("Invalid UTF-8"));
        g_clear_error(&error);

        ret = escaped_str;
    }

#ifdef G_OS_WIN32

#endif

    return ret;
}
