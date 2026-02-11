tracker_date_time_get_local_date (const GValue *value)
{
	gdouble local_timestamp;

	g_return_val_if_fail (G_VALUE_HOLDS (value, TRACKER_TYPE_DATE_TIME), 0);


	local_timestamp = tracker_date_time_get_time (value) + tracker_date_time_get_offset (value);
	return (gint) (local_timestamp / 3600 / 24);
}
