main_window_documents_list_action_activate (MainWindowDocuments* self, GtkAction* action) {
	DocumentsPanel* _tmp0_ = NULL;
	GtkRadioAction* radio_action = NULL;
	GtkAction* _tmp1_ = NULL;
	GtkRadioAction* _tmp2_ = NULL;
	GtkRadioAction* _tmp3_ = NULL;
	gboolean _tmp4_ = FALSE;
	DocumentsPanel* _tmp5_ = NULL;
	GtkRadioAction* _tmp6_ = NULL;
	gint _tmp7_ = 0;
	g_return_if_fail (self != NULL);
	g_return_if_fail (action != NULL);
	_tmp0_ = self->priv->_documents_panel;
	g_return_if_fail (_tmp0_ != NULL);
	_tmp1_ = action;
	_tmp2_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp1_, GTK_TYPE_RADIO_ACTION) ? ((GtkRadioAction*) _tmp1_) : NULL);
	radio_action = _tmp2_;
	_tmp3_ = radio_action;
	_tmp4_ = gtk_toggle_action_get_active ((GtkToggleAction*) _tmp3_);
	if (!_tmp4_) {
		_g_object_unref0 (radio_action);
		return;
	}
	_tmp5_ = self->priv->_documents_panel;
	_tmp6_ = radio_action;
	_tmp7_ = gtk_radio_action_get_current_value (_tmp6_);
	gtk_notebook_set_current_page ((GtkNotebook*) _tmp5_, _tmp7_);
	_g_object_unref0 (radio_action);
}
