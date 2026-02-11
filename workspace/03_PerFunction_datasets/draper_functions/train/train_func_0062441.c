write_attr_interval(struct thermometer *t, DBusMessage *msg,
								uint16_t value)
{
	struct tmp_interval_data *data;
	struct characteristic *ch;
	uint8_t atval[2];

	if (t->attrib == NULL)
		return btd_error_not_connected(msg);

	ch = get_characteristic(t, MEASUREMENT_INTERVAL_UUID);
	if (ch == NULL)
		return btd_error_not_available(msg);

	if (value < t->min || value > t->max)
		return btd_error_invalid_args(msg);

	att_put_u16(value, &atval[0]);

	data = g_new0(struct tmp_interval_data, 1);
	data->thermometer = t;
	data->interval = value;
	gatt_write_char(t->attrib, ch->attr.value_handle, atval, 2,
						write_interval_cb, data);

	return dbus_message_new_method_return(msg);
}
