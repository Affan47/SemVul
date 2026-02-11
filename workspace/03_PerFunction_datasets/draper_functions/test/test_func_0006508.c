seahorse_util_get_date_string (const time_t time)
{
	GDate *created_date;
	gchar *created_string;

	if (time == 0)
		return "0";

	created_date = g_date_new ();
	g_date_set_time_t (created_date, time);
	created_string = g_new (gchar, 11);
	g_date_strftime (created_string, 11, "%Y-%m-%d", created_date);
	return created_string;
}
