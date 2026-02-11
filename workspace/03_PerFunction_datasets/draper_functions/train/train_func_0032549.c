attrib_channel_detach(GAttrib *attrib, guint id)
{
	struct gatt_server *server;
	struct gatt_channel *channel;
	GError *gerr = NULL;
	GIOChannel *io;
	bdaddr_t src;
	GSList *l;

	io = g_attrib_get_channel(attrib);

	bt_io_get(io, BT_IO_L2CAP, &gerr, BT_IO_OPT_SOURCE_BDADDR, &src,
							BT_IO_OPT_INVALID);

	if (gerr != NULL) {
		error("bt_io_get: %s", gerr->message);
		g_error_free(gerr);
		return FALSE;
	}

	server = find_gatt_server(&src);
	if (server == NULL)
		return FALSE;

	l = g_slist_find_custom(server->clients, GUINT_TO_POINTER(id),
								channel_id_cmp);
	if (!l)
		return FALSE;

	channel = l->data;

	g_attrib_unregister(channel->attrib, channel->id);
	channel_remove(channel);

	return TRUE;
}
