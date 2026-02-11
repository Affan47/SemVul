empty_log_handler (const gchar *log_domain, GLogLevelFlags log_level,
                        const gchar *message, gpointer user_data) {
	if (log_level & (G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION)) {
		exit (1);
	}
}
