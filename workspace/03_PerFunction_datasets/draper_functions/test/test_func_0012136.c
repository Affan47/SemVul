stats_append(struct connman_service *service,
				const char *counter,
				struct connman_stats_counter *counters,
				connman_bool_t append_all)
{
	DBusMessageIter array, dict;
	DBusMessage *msg;

	DBG("service %p counter %s", service, counter);

	msg = dbus_message_new(DBUS_MESSAGE_TYPE_METHOD_CALL);
	if (msg == NULL)
		return;

	dbus_message_append_args(msg, DBUS_TYPE_OBJECT_PATH,
				&service->path, DBUS_TYPE_INVALID);

	dbus_message_iter_init_append(msg, &array);


	connman_dbus_dict_open(&array, &dict);

	stats_append_counters(&dict, &service->stats.data,
				&counters->stats.data, append_all);

	connman_dbus_dict_close(&array, &dict);


	connman_dbus_dict_open(&array, &dict);

	stats_append_counters(&dict, &service->stats_roaming.data,
				&counters->stats_roaming.data, append_all);

	connman_dbus_dict_close(&array, &dict);

	__connman_counter_send_usage(counter, msg);
}
