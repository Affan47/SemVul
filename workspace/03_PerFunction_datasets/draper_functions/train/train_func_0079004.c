log4glib_handler(const gchar     *log_domain,
                 GLogLevelFlags  log_level,
                 const gchar     *message,
                 gpointer        user_data)
{
    if (G_LIKELY(!qof_log_check(log_domain, log_level)))
        return;

    {
        char timestamp_buf[10];
        time64 now;
        struct tm now_tm;
        const char *format_24hour =
#ifdef G_OS_WIN32
            "%H:%M:%S"
#else
            "%T"
#endif
            ;
        gchar *level_str = qof_log_level_to_string(log_level);
        now = gnc_time (NULL);
        gnc_localtime_r (&now, &now_tm);
        qof_strftime(timestamp_buf, 9, format_24hour, &now_tm);

        fprintf(fout, "* %s %*s <%s> %*s%s%s",
                timestamp_buf,
                5, level_str,
                (log_domain == NULL ? "" : log_domain),
                qof_log_num_spaces, "",
                message,
                (g_str_has_suffix(message, "\n") ? "" : "\n"));
        fflush(fout);
    }


}
