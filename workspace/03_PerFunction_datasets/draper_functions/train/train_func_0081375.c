wejpscroller_new(guint scroll_delay, gboolean smart)
{
	GtkWidget *ws = GTK_WIDGET(g_object_new(WEJPSCROLLER_TYPE, NULL));
	WEJPSCROLLER(ws)->scroll_delay = scroll_delay;
	WEJPSCROLLER(ws)->smart_scrolling = smart;
	if (scroll_delay != 0) {
		WEJPSCROLLER(ws)->scroll = TRUE;
	} else {
		WEJPSCROLLER(ws)->scroll = FALSE;
	}
	WEJPSCROLLER(ws)->shortmessage_timeout = 0;
	WEJPSCROLLER(ws)->shortmessage_text_backup[0] = '\0';
	if (WEJPSCROLLER(ws)->scroll)
		g_timeout_add(WEJPSCROLLER(ws)->scroll_delay, &cb_timer, ws);
	else
		g_timeout_add(100, &cb_timer, ws);
	return ws;
}
