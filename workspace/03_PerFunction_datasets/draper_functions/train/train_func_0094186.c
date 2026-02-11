update_watcher(gpointer data, gpointer user_data)
{
	struct watcher *w = data;
	struct measurement *m = user_data;
	DBusConnection *conn = w->t->conn;
	DBusMessageIter iter;
	DBusMessageIter dict;
	DBusMessage *msg;

	msg = dbus_message_new_method_call(w->srv, w->path,
				"org.bluez.ThermometerWatcher",
				"MeasurementReceived");
	if (msg == NULL)
		return;

	dbus_message_iter_init_append(msg, &iter);

	dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY,
			DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
			DBUS_TYPE_STRING_AS_STRING DBUS_TYPE_VARIANT_AS_STRING
			DBUS_DICT_ENTRY_END_CHAR_AS_STRING, &dict);

	dict_append_entry(&dict, "Exponent", DBUS_TYPE_INT16, &m->exp);
	dict_append_entry(&dict, "Mantissa", DBUS_TYPE_INT32, &m->mant);
	dict_append_entry(&dict, "Unit", DBUS_TYPE_STRING, &m->unit);

	if (m->suptime)
		dict_append_entry(&dict, "Time", DBUS_TYPE_UINT64, &m->time);

	dict_append_entry(&dict, "Type", DBUS_TYPE_STRING, &m->type);
	dict_append_entry(&dict, "Measurement", DBUS_TYPE_STRING, &m->value);

	dbus_message_iter_close_container(&iter, &dict);

	dbus_message_set_no_reply(msg, TRUE);
	g_dbus_send_message(conn, msg);
}
