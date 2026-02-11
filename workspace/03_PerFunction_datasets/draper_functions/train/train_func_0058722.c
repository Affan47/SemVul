completion_provider_init_calltip_window (CompletionProvider* self) {
	GtkSourceCompletionInfo* _tmp0_ = NULL;
	GtkLabel* _tmp1_ = NULL;
	GtkSourceCompletionInfo* _tmp2_ = NULL;
	GtkLabel* _tmp3_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = gtk_source_completion_info_new ();
	g_object_ref_sink (_tmp0_);
	_g_object_unref0 (self->priv->_calltip_window);
	self->priv->_calltip_window = _tmp0_;
	_tmp1_ = (GtkLabel*) gtk_label_new (NULL);
	g_object_ref_sink (_tmp1_);
	_g_object_unref0 (self->priv->_calltip_window_label);
	self->priv->_calltip_window_label = _tmp1_;
	_tmp2_ = self->priv->_calltip_window;
	_tmp3_ = self->priv->_calltip_window_label;
	gtk_container_add ((GtkContainer*) _tmp2_, (GtkWidget*) _tmp3_);
}
