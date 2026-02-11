format_time(gint seconds)
{
	gint hours, minutes;

	if (seconds < 0)
		seconds = 0;

	if (seconds < 60)
		return g_strdup_printf(ngettext("%'d second",
					"%'d seconds", seconds), seconds);

	if (seconds < 60 * 60) {
		minutes = (seconds + 30) / 60;
		return g_strdup_printf(ngettext("%'d minute",
					"%'d minutes", minutes), minutes);
	}

	hours = seconds / (60 * 60);

	if (seconds < 60 * 60 * 4) {
		gchar *res, *h, *m;

		minutes = (seconds - hours * 60 * 60 + 30) / 60;

		h = g_strdup_printf(ngettext("%'d hour",
					"%'d hours", hours), hours);
		m = g_strdup_printf(ngettext("%'d minute",
					"%'d minutes", minutes), minutes);
		res = g_strconcat(h, ", ", m, NULL);
		g_free(h);
		g_free(m);
		return res;
	}

	return g_strdup_printf(ngettext("approximately %'d hour",
				"approximately %'d hours", hours), hours);
}
