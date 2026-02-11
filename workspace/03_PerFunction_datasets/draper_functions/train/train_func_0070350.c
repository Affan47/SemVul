__lambda39_ (MainWindowDocuments* self, GtkWidget* pg, guint page_num) {
	guint _tmp0_ = 0U;
	g_return_if_fail (pg != NULL);
	_tmp0_ = page_num;
	main_window_documents_set_active_document (self, _tmp0_);
	main_window_documents_update_sensitivity (self);
}
