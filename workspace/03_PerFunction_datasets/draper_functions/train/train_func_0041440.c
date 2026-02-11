cd_sensor_debug_data (CdSensorDebugMode debug_mode,
		      const guint8 *data,
		      gsize length)
{
	guint i;
	if (debug_mode == CD_SENSOR_DEBUG_MODE_REQUEST)
		g_print ("%c[%dm request\t", 0x1B, 31);
	else if (debug_mode == CD_SENSOR_DEBUG_MODE_RESPONSE)
		g_print ("%c[%dm response\t", 0x1B, 34);
	for (i = 0; i <  length; i++)
		g_print ("%02x [%c]\t", data[i], g_ascii_isprint (data[i]) ? data[i] : '?');
	g_print ("%c[%dm\n", 0x1B, 0);
}
