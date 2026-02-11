update_nmea_vtg(void)
{
	g_string_assign(nmea_vtg, "$GPVTG");

	if (!COURSE_DIRECTION_IS_VALID) {
		g_string_append_c(nmea_vtg, ',');
		g_string_append_c(nmea_vtg, ',');
	} else {
		g_string_append_printf(nmea_vtg, ",%04.2f,T", course_direction);
	}

	g_string_append_c(nmea_vtg, ',');
	g_string_append_c(nmea_vtg, ',');

	if (!COURSE_SPEED_IS_VALID) {
		g_string_append_c(nmea_vtg, ',');
		g_string_append_c(nmea_vtg, ',');
		g_string_append_c(nmea_vtg, ',');
		g_string_append_c(nmea_vtg, ',');
	} else {
		g_string_append_printf(nmea_vtg, ",%05.3f,N,%05.3f,K",
			course_speed, course_speed * KNOTS_TO_KPH);
	}

	add_nmea_checksum(nmea_vtg);
}
