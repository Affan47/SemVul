add_nmea_time(GString *nmea)
{
	if (time_seconds <= 0) {
		g_string_append_c(nmea, ',');
	} else {
		struct tm *tm;
		time_t seconds;

		seconds = time_seconds;
		tm = gmtime(&seconds);

		g_string_append_printf(nmea, ",%02d%02d%02d.00",
			tm->tm_hour, tm->tm_min, tm->tm_sec);
	}
}
