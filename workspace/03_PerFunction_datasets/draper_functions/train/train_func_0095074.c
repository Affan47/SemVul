hlight_toggle_searched(GtkTextBuffer *buffer)
{
	if (!searched_flag) {
		g_signal_handlers_unblock_by_func(G_OBJECT(buffer),
			G_CALLBACK(cb_changed), NULL);
		searched_flag = TRUE;
	} else {
		g_signal_handlers_block_by_func(G_OBJECT(buffer),
			G_CALLBACK(cb_changed), NULL);
		searched_flag = FALSE;
	}
	return searched_flag;
}
