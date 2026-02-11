get_timestamp(THEME_REC *theme, TEXT_DEST_REC *dest, time_t t)
{
	char *format, str[256];
	struct tm *tm;
	int diff;

	if ((timestamp_level & dest->level) == 0)
		return NULL;


	if (dest->flags & PRINT_FLAG_UNSET_TIMESTAMP)
		return NULL;

	if ((dest->flags & PRINT_FLAG_SET_TIMESTAMP) == 0 &&
	    (dest->level & (MSGLEVEL_NEVER|MSGLEVEL_LASTLOG)) != 0)
		return NULL;


	if (timestamp_timeout > 0) {
		diff = t - dest->window->last_timestamp;
		dest->window->last_timestamp = t;
		if (diff < timestamp_timeout)
			return NULL;
	}

	tm = localtime(&t);
	format = format_get_text_theme(theme, MODULE_NAME, dest,
				       TXT_TIMESTAMP);
	if (strftime(str, sizeof(str), format, tm) <= 0)
		str[0] = '\0';
	g_free(format);
	return g_strdup(str);
}
