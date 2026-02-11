add_sats(GString *string)
{
	unsigned i, count;

	if (satellite_satellitec == 0) {
		g_string_append(string, ",Y=?");
		return;
	}

	g_string_append(string, ",Y=-");

	if (time_seconds <= 0) {
		g_string_append(string, " ? ");
	} else {
		g_string_append_printf(string, " %d.000 ", time_seconds);
	}

	count = MIN(satellite_satellitec, 12);

	g_string_append_printf(string, "%d:", count);

	for (i = 0; i < count; i++) {
		g_string_append_printf(string, "%d %d %d %d %d:",
			satellite_satellitev[i].prn,
			satellite_satellitev[i].elevation,
			satellite_satellitev[i].azimuth,
			satellite_satellitev[i].snr,
			satellite_satellitev[i].used);
	}
}
