gdata_parser_int64_from_date (const gchar *date, gint64 *_time)
{
	gchar *iso8601_date;
	gboolean success;
	GTimeVal time_val;

	if (strlen (date) != 10 && strlen (date) != 8)
		return FALSE;


	iso8601_date = g_strdup_printf ("%sT00:00:00Z", date);
	success = g_time_val_from_iso8601 (iso8601_date, &time_val);
	g_free (iso8601_date);

	if (success == TRUE)
		*_time = time_val.tv_sec;

	return success;
}
