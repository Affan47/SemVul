tracker_needle_show_info_message (TrackerNeedle* self, const gchar* message, GtkMessageType type) {
	GtkInfoBar* _tmp0_ = NULL;
	GtkMessageType _tmp1_ = 0;
	GtkLabel* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	GtkInfoBar* _tmp4_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (message != NULL);
	_tmp0_ = self->priv->info_bar;
	_tmp1_ = type;
	gtk_info_bar_set_message_type (_tmp0_, _tmp1_);
	_tmp2_ = self->priv->info_bar_label;
	_tmp3_ = message;
	gtk_label_set_markup (_tmp2_, _tmp3_);
	_tmp4_ = self->priv->info_bar;
	gtk_widget_show ((GtkWidget*) _tmp4_);
}
