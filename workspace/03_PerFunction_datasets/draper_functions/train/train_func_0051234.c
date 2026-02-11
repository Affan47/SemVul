make_ts (GdaHandlerTime *hdl, const gchar *value, LocaleSetting *locale)
{
	GDateTime *ts;
	const gchar *end_ptr;
	GDate vdate;
	GdaTime vtime;
	memset (&vtime, 0, sizeof (GdaTime));
	vtime.timezone = GDA_TIMEZONE_INVALID;

	gboolean retval;
	retval = make_date (hdl, &vdate, value, locale, &end_ptr);
	if (retval) {
		if (*end_ptr != ' ')
			retval = FALSE;
		else
			retval = make_time (hdl, &vtime, end_ptr + 1);
	}
	if (!retval)
		return NULL;

	GTimeZone *tz;
	if (vtime.timezone != GDA_TIMEZONE_INVALID) {
		gchar *tzdef;
		if (vtime.timezone >= 0)
			tzdef = g_strdup_printf ("+%02d", (gint) (vtime.timezone / 3600));
		else
			tzdef = g_strdup_printf ("-%02d", (gint) (- vtime.timezone / 3600));
		tz = g_time_zone_new (tzdef);
		g_free (tzdef);
	}
	else
		tz = g_time_zone_new_local ();
	ts = g_date_time_new (tz, vdate.year, vdate.month, vdate.day,
			      vtime.hour, vtime.minute, (gdouble) vtime.second + vtime.fraction);
	g_time_zone_unref (tz);

	return ts;
}
