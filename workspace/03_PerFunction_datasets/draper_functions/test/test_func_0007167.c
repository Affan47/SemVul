on_gm_world_view_world_error(GmWorld *world, gchar *text, gint code,
		GmWorldView *view) {
	gchar *line;

	switch (code) {
		case GM_NET_ERROR_CONNECTING:
			line = g_strdup_printf(_("Connect failed: %s"), text);
		break;
		case GM_NET_ERROR_DISCONNECTED:
			line = g_strdup_printf(_("Connection lost... (%s)"), text);
		break;
		default:
			line = g_strdup_printf(_("Error: %s"), text);
		break;
	}

	gm_world_status(world, line);
	g_free(line);
}
