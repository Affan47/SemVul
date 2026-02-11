strip_line (gchar * line, scan_data * data)
{
	gint count;

	if (! g_regex_match_simple ("^\\d+/\\w", line, 0, 0)) {
		return 0;
	}

	count = sscanf (line, SCAN_FORMAT,
			data->port, data->state, data->service);

	return count;
}
