math_window_critical_error (MathWindow* self, const gchar* title, const gchar* contents) {
	GtkMessageDialog* dialog = NULL;
	const gchar* _tmp0_ = NULL;
	GtkMessageDialog* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (title != NULL);
	g_return_if_fail (contents != NULL);
	_tmp0_ = title;
	_tmp1_ = (GtkMessageDialog*) gtk_message_dialog_new (NULL, 0, GTK_MESSAGE_ERROR, GTK_BUTTONS_NONE, "%s", _tmp0_);
	g_object_ref_sink (_tmp1_);
	dialog = _tmp1_;
	_tmp2_ = contents;
	gtk_message_dialog_format_secondary_text (dialog, "%s", _tmp2_);
	gtk_dialog_add_buttons ((GtkDialog*) dialog, GTK_STOCK_QUIT, GTK_RESPONSE_ACCEPT, NULL);
	gtk_dialog_run ((GtkDialog*) dialog);
	gtk_widget_destroy ((GtkWidget*) self);
	_g_object_unref0 (dialog);
}
