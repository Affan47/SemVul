server_start(const bdaddr_t *src)
{
	struct input_server *server;
	GError *err = NULL;

	server = g_new0(struct input_server, 1);
	bacpy(&server->src, src);

	server->ctrl = bt_io_listen(BT_IO_L2CAP, connect_event_cb, NULL,
				server, NULL, &err,
				BT_IO_OPT_SOURCE_BDADDR, src,
				BT_IO_OPT_PSM, L2CAP_PSM_HIDP_CTRL,
				BT_IO_OPT_SEC_LEVEL, BT_IO_SEC_LOW,
				BT_IO_OPT_INVALID);
	if (!server->ctrl) {
		error("Failed to listen on control channel");
		g_error_free(err);
		g_free(server);
		return -1;
	}

	server->intr = bt_io_listen(BT_IO_L2CAP, NULL, confirm_event_cb,
				server, NULL, &err,
				BT_IO_OPT_SOURCE_BDADDR, src,
				BT_IO_OPT_PSM, L2CAP_PSM_HIDP_INTR,
				BT_IO_OPT_SEC_LEVEL, BT_IO_SEC_LOW,
				BT_IO_OPT_INVALID);
	if (!server->intr) {
		error("Failed to listen on interrupt channel");
		g_io_channel_unref(server->ctrl);
		g_error_free(err);
		g_free(server);
		return -1;
	}

	servers = g_slist_append(servers, server);

	return 0;
}
