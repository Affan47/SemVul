resource_available_cb (G_GNUC_UNUSED GSSDPResourceBrowser *resource_browser,
                       const char                         *usn,
                       GList                              *locations)
{

        char **usn_tokens;
        char *uuid;
        char *device_type = NULL;
        time_t current_time;
        struct tm *tm;
        char *first_notify;

        current_time = time (NULL);
        tm = localtime (&current_time);
        first_notify = g_strdup_printf ("%02d:%02d",
        tm->tm_hour, tm->tm_min);

        usn_tokens = g_strsplit (usn, "::", -1);
        g_assert (usn_tokens != NULL && usn_tokens[0] != NULL);

        uuid = usn_tokens[0] + 5;

        if (usn_tokens[1]) {
                char **urn_tokens;

                urn_tokens = g_strsplit (usn_tokens[1], ":device:", -1);

                if (urn_tokens[1])
                        device_type = g_strdup (urn_tokens[1]);
                g_strfreev (urn_tokens);
        }


        append_device (uuid,
                       first_notify,
                       device_type,
                       (char *) locations->data);

        if (device_type)
                g_free (device_type);
        g_free (first_notify);
        g_strfreev (usn_tokens);
}
