main_window_support_drag_and_drop (MainWindow* self) {
	GtkTargetEntry* _tmp0_ = NULL;
	GtkTargetEntry* _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = g_new0 (GtkTargetEntry, 0);
	_tmp1_ = _tmp0_;
	_tmp1__length1 = 0;
	gtk_drag_dest_set ((GtkWidget*) self, GTK_DEST_DEFAULT_ALL, _tmp1_, 0, GDK_ACTION_COPY);
	_tmp1_ = (g_free (_tmp1_), NULL);
	gtk_drag_dest_add_uri_targets ((GtkWidget*) self);
	g_signal_connect_object ((GtkWidget*) self, "drag-data-received", (GCallback) ___lambda131__gtk_widget_drag_data_received, self, 0);
}
