get_date(VCalMeeting *meet, int start)
{
	struct tm *lt;
	time_t t;
	guint d, m, y;
	int dst_offset = 0;
	struct tm buft;

	tzset();

	t = time(NULL);
#ifdef G_OS_WIN32
	if (t < 0)
		t = 1;
#endif
	lt = localtime_r(&t, &buft);

	gtk_calendar_get_date(GTK_CALENDAR(start ? meet->start_c : meet->end_c), &y, &m, &d);
	lt->tm_mday = d;
	lt->tm_mon  = m;
	lt->tm_year = y - 1900;
	lt->tm_hour = 0;
	lt->tm_min  = 0;
	lt->tm_sec  = 0;

	if (start) {
		get_time_from_combo(meet->start_time, &lt->tm_hour, &lt->tm_min);
	} else {
		get_time_from_combo(meet->end_time, &lt->tm_hour, &lt->tm_min);
	}

	debug_print("%d %d %d, %d:%d\n", lt->tm_mday, lt->tm_mon, lt->tm_year, lt->tm_hour, lt->tm_min);
	t = mktime(lt);

	dst_offset = get_current_gmt_offset() - get_gmt_offset_at_time(t);
	debug_print("DST change offset to apply to time %d\n", dst_offset);
	t += dst_offset;
	debug_print("%s\n", ctime(&t));
	return g_strdup(icaltime_as_ical_string(icaltime_from_timet(t, FALSE)));
}
