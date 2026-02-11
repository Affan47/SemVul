dvb_id_bus_recorder_AddTimer (DVBIDBusRecorder* self, guint channel, gint start_year, gint start_month, gint start_day, gint start_hour, gint start_minute, guint duration, guint32* timer_id, GError** error) {
	g_return_val_if_fail (self != NULL, FALSE);
	return DVB_ID_BUS_RECORDER_GET_INTERFACE (self)->AddTimer (self, channel, start_year, start_month, start_day, start_hour, start_minute, duration, timer_id, error);
}
