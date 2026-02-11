alm_delete_history_dialog_construct (GType object_type, GtkButton* del_button) {
	AlmDeleteHistoryDialog * self = NULL;
	const gchar* _tmp0_ = NULL;
	ZeitgeistLog* _tmp1_ = NULL;
	GtkButton* _tmp2_ = NULL;
	AlmCalendarWidget* _tmp3_ = NULL;
	g_return_val_if_fail (del_button != NULL, NULL);
	self = (AlmDeleteHistoryDialog*) g_object_new (object_type, NULL);
	_tmp0_ = _ ("Clear Usage Data");
	gtk_window_set_title ((GtkWindow*) self, _tmp0_);
	gtk_window_set_destroy_with_parent ((GtkWindow*) self, TRUE);
	gtk_window_set_skip_taskbar_hint ((GtkWindow*) self, TRUE);
	gtk_container_set_border_width ((GtkContainer*) self, (guint) 12);
	gtk_window_set_resizable ((GtkWindow*) self, FALSE);
	_tmp1_ = zeitgeist_log_new ();
	_g_object_unref0 (self->priv->zg_log);
	self->priv->zg_log = _tmp1_;
	_tmp2_ = del_button;
	_tmp3_ = alm_calendar_widget_new (_tmp2_);
	g_object_ref_sink (_tmp3_);
	_g_object_unref0 (self->priv->calendar_box);
	self->priv->calendar_box = _tmp3_;
	alm_delete_history_dialog_set_up_ui (self);
	return self;
}
