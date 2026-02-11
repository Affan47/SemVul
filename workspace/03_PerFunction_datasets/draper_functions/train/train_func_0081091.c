hdp_mdl_reconn_cb(struct mcap_mdl *mdl, GError *err, gpointer data)
{
	struct hdp_tmp_dc_data *dc_data = data;
	DBusMessage *reply;
	int fd;

	if (err != NULL) {
		struct hdp_channel *chan = dc_data->hdp_chann;
		GError *gerr = NULL;

		error("%s", err->message);
		reply = g_dbus_create_error(dc_data->msg,
					ERROR_INTERFACE ".HealthError",
					"Cannot reconnect: %s", err->message);
		g_dbus_send_message(dc_data->conn, reply);


		if (!mcap_mdl_abort(chan->mdl, abort_mdl_cb, NULL, NULL,
								&gerr)) {
			error("%s", gerr->message);
			g_error_free(gerr);
		}
		return;
	}

	fd = mcap_mdl_get_fd(dc_data->hdp_chann->mdl);
	if (fd < 0) {
		reply = g_dbus_create_error(dc_data->msg,
						ERROR_INTERFACE ".HealthError",
						"Cannot get file descriptor");
		g_dbus_send_message(dc_data->conn, reply);
		return;
	}

	reply = g_dbus_create_reply(dc_data->msg, DBUS_TYPE_UNIX_FD,
							&fd, DBUS_TYPE_INVALID);
	g_dbus_send_message(dc_data->conn, reply);

	g_dbus_emit_signal(dc_data->conn,
			device_get_path(dc_data->hdp_chann->dev->dev),
			HEALTH_DEVICE, "ChannelConnected",
			DBUS_TYPE_OBJECT_PATH, &dc_data->hdp_chann->path,
			DBUS_TYPE_INVALID);
}
