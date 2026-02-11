http_request_set_accept_language (SoupMessage *message)
{
        char *locale, *lang;
        int dash_index;
        GString *tmp;

#ifdef G_OS_WIN32

        return;
#else

        locale = setlocale (LC_MESSAGES, NULL);

        if (locale == NULL)
                return;

        if (strcmp (locale, "C") == 0)
                return;

        lang = g_strdup (locale);

        dash_index = http_language_from_locale (lang);

        tmp = g_string_new (lang);
        g_string_append (tmp, ";q=1");


        if (dash_index > 0) {
                g_string_append (tmp, ", ");

                lang[dash_index] = '\0';
                g_string_append (tmp, lang);
                g_string_append (tmp, ";q=0.5");
        }

        g_free (lang);

        soup_message_headers_append (message->request_headers,
                                     "Accept-Language",
                                     tmp->str);

        g_string_free (tmp, TRUE);
#endif
}
