on_widget_destroy(GtkWidget *widget, gpointer data) {
	GmSchemedFlags flags = GPOINTER_TO_INT(data);
	GmColorTable *table = GM_COLOR_TABLE(g_object_get_data(G_OBJECT(widget),
			"gm_color_table"));

	if (flags & GM_SCHEMED_COLORS) {
		g_signal_handlers_disconnect_by_func(table,
				G_CALLBACK(on_color_changed), widget);
	}
	if (flags & GM_SCHEMED_FONT) {
		g_signal_handlers_disconnect_by_func(table,
				G_CALLBACK(on_font_changed), widget);
	}


	g_signal_handlers_disconnect_by_func(widget, G_CALLBACK(on_widget_destroy),
			data);
}
