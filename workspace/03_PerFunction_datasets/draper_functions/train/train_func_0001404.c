set_powered(struct connman_technology *technology,
				DBusMessage *msg, connman_bool_t powered)
{
	DBusMessage *reply = NULL;
	int err = 0;

	if (technology->rfkill_driven && technology->hardblocked == TRUE) {
		err = -EACCES;
		goto make_reply;
	}

	if (powered == TRUE)
		err = technology_enable(technology);
	else
		err = technology_disable(technology);

	if (err != -EBUSY) {
		technology->enable_persistent = powered;
		technology_save(technology);
	}

make_reply:
	if (err == -EINPROGRESS) {
		technology->pending_reply = dbus_message_ref(msg);
		technology->pending_timeout = g_timeout_add_seconds(10,
					technology_pending_reply, technology);
	} else if (err == -EALREADY) {
		if (powered == TRUE)
			reply = __connman_error_already_enabled(msg);
		else
			reply = __connman_error_already_disabled(msg);
	} else if (err < 0)
		reply = __connman_error_failed(msg, -err);
	else
		reply = g_dbus_create_reply(msg, DBUS_TYPE_INVALID);

	return reply;
}
