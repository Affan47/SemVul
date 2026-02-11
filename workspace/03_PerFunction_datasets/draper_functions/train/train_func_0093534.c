log_output (const gchar    *domain,
            GLogLevelFlags  log_level,
            const gchar    *message)
{
	time_t        now;
	gchar         time_str[64];
	gchar        *output;
	struct tm    *local_time;
	const gchar  *log_level_str;
	static gsize  size = 0;

	g_return_if_fail (initialized == TRUE);
	g_return_if_fail (message != NULL && message[0] != '\0');


#if GLIB_CHECK_VERSION (2,31,0)
	g_mutex_lock (&mutex);
#else
	g_mutex_lock (mutex);
#endif


	if (size > (10 << 20) && fd) {
		rewind (fd);

		if (ftruncate (fileno (fd), 0) != 0) {

		}

		size = 0;
	}

	now = time ((time_t *) NULL);
	local_time = localtime (&now);
	strftime (time_str, 64, "%d %b %Y, %H:%M:%S:", local_time);

	switch (log_level) {
	case G_LOG_LEVEL_WARNING:
		log_level_str = "-Warning **";
		break;

	case G_LOG_LEVEL_CRITICAL:
		log_level_str = "-Critical **";
		break;

	case G_LOG_LEVEL_ERROR:
		log_level_str = "-Error **";
		break;
	case G_LOG_FLAG_RECURSION:
	case G_LOG_FLAG_FATAL:
	case G_LOG_LEVEL_MESSAGE:
	case G_LOG_LEVEL_INFO:
	case G_LOG_LEVEL_DEBUG:
	case G_LOG_LEVEL_MASK:
	default:
		log_level_str = NULL;
		break;
	}

	output = g_strdup_printf ("%s%s %s%s: %s",
	                          log_level_str ? "\n" : "",
	                          time_str,
	                          domain,
	                          log_level_str ? log_level_str : "",
	                          message);

	if (G_UNLIKELY (fd == NULL)) {
		FILE *f;

		if (log_level == G_LOG_LEVEL_WARNING ||
		    log_level == G_LOG_LEVEL_CRITICAL ||
		    log_level == G_LOG_LEVEL_ERROR) {
			f = stderr;
		} else {
			f = stdout;
		}

		g_fprintf (f, "%s\n", output);
		fflush (f);
	} else {
		size += g_fprintf (fd, "%s\n", output);
		fflush (fd);
	}

	g_free (output);

#if GLIB_CHECK_VERSION (2,31,0)
	g_mutex_unlock (&mutex);
#else
	g_mutex_unlock (mutex);
#endif
}
