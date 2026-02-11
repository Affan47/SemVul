connman_manager_init(connman_property_changed_cb_f property_changed_cb,
							void *user_data)
{
	DBusMessage *message = NULL;
	int err = -EINVAL;

	if (connman == NULL)
		return -EINVAL;

	if (manager != NULL)
		return 0;

	manager = g_try_malloc0(sizeof(struct connman_manager));
	if (manager == NULL)
		return -ENOMEM;

	manager->dbus_cnx = dbus_connection_ref(connman->dbus_cnx);

	manager->property_changed_cb = property_changed_cb;

	message = dbus_message_new_method_call(CONNMAN_DBUS_NAME,
						CONNMAN_MANAGER_PATH,
						CONNMAN_MANAGER_INTERFACE,
						"GetProperties");
	if (message == NULL) {
		err = -ENOMEM;
		goto error;
	}

	if (dbus_connection_send_with_reply(manager->dbus_cnx, message,
					&manager->get_properties_call,
					DBUS_TIMEOUT_USE_DEFAULT) == FALSE)
		goto error;

	if (dbus_pending_call_set_notify(manager->get_properties_call,
				get_properties_callback, NULL, NULL) == FALSE)
		goto error;

	manager->property_changed_wid = g_dbus_add_signal_watch(
						manager->dbus_cnx,
						CONNMAN_DBUS_NAME,
						CONNMAN_MANAGER_PATH,
						CONNMAN_MANAGER_INTERFACE,
						"PropertyChanged",
						property_changed_signal_cb,
						NULL, NULL);
	if (manager->property_changed_wid == 0)
		goto error;

	manager->property_user_data = user_data;

	dbus_message_unref(message);

	return 0;

error:
	if (message != NULL)
		dbus_message_unref(message);

	connman_manager_finalize();

	return err;
}
