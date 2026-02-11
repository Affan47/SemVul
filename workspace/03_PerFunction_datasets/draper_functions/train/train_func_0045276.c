abraca_filter_view_create_drag_n_drop (AbracaFilterView* self) {
	g_return_if_fail (self != NULL);
	gtk_tree_view_enable_model_drag_source ((GtkTreeView*) self, GDK_BUTTON1_MASK, ABRACA_FILTER_VIEW__target_entries, G_N_ELEMENTS (ABRACA_FILTER_VIEW__target_entries), GDK_ACTION_MOVE);
	g_signal_connect_object ((GtkWidget*) self, "drag-data-get", (GCallback) _abraca_filter_view_on_drag_data_get_gtk_widget_drag_data_get, self, 0);
}
