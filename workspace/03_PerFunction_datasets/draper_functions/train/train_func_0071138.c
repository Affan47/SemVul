on_gm_world_net_bytes_recv(GmNet *net, gchar *text, gint len,
		GmWorld *world) {
	gchar *all, *utext, *ptr, *start;
	gunichar ch, prev;

	utext = gm_to_utf8_with_fallback(text, len,
			gm_options_get(world->priv->options, "charset"), "?");

	if (!utext) {
		gm_debug_msg(DEBUG_DEFAULT, "GmWorld.NetBytesRecv: conversion failed!");
		utext = g_strndup(text, len);
	}

	if (world->priv->buffer != NULL) {
		all = g_strconcat(world->priv->buffer, utext, NULL);
		g_free(utext);
		g_free(world->priv->buffer);
		world->priv->buffer = NULL;
	} else {
		all = utext;
	}

	ptr = start = all;
	prev = 0;


	while ((ch = g_utf8_get_char(ptr)) != '\0') {
		if (ch == '\n') {
			gm_world_process_line(world, start, ptr - start -
					(prev == '\r' ? 1 : 0));
			ptr = start = g_utf8_next_char(ptr);


			if (g_utf8_get_char(ptr) == '\r') {
				ptr = start = g_utf8_next_char(ptr);
			}
		} else {
			ptr = g_utf8_next_char(ptr);
		}

		prev = ch;
	}

	if (*start != '\0') {
		world->priv->buffer = g_strdup(start);
	}

	g_free(all);
}
