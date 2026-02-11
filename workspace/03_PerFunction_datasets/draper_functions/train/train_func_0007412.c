get_properties_callback(DBusPendingCall *pending, void *user_data)
{
	dbus_bool_t offlinemode;
	DBusMessageIter arg;
	DBusMessage *reply;
	const char *state;

	if (dbus_pending_call_get_completed(pending) == FALSE)
		return;

	manager->get_properties_call = NULL;

	reply = dbus_pending_call_steal_reply(pending);
	if (reply == NULL)
		goto error;

	if (dbus_message_iter_init(reply, &arg) == FALSE)
		goto error;

	if (cui_dbus_get_dict_entry_basic(&arg,
				PROPERTY(MANAGER_STATE),
				DBUS_TYPE_STRING, &state) == 0) {
		manager->state = string2enum_state(state);
		update_manager_property(MANAGER_STATE);
	}

	if (cui_dbus_get_dict_entry_basic(&arg,
				PROPERTY(MANAGER_OFFLINEMODE),
				DBUS_TYPE_BOOLEAN, &offlinemode) == 0) {
		manager->offlinemode = offlinemode;
		update_manager_property(MANAGER_OFFLINEMODE);
	}

error:
	if (reply != NULL)
		dbus_message_unref(reply);

	dbus_pending_call_unref(pending);
}
