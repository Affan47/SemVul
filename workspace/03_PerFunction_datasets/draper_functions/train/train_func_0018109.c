abraca_medialib_info_dialog_add_id (AbracaMedialib* self, guint mid) {
	AbracaMedialibInfoDialog* _tmp0_;
	AbracaMedialibInfoDialog* _tmp8_;
	guint _tmp9_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->info_dialog;
	if (_tmp0_ == NULL) {
		AbracaMedialibInfoDialog* _tmp1_ = NULL;
		AbracaMedialibInfoDialog* _tmp2_;
		GtkWindow* _tmp3_;
		AbracaMedialibInfoDialog* _tmp4_;
		AbracaClient* _tmp5_;
		AbracaMedialibInfoDialog* _tmp6_;
		AbracaMedialibInfoDialog* _tmp7_;
		_tmp1_ = abraca_medialib_info_dialog_build ();
		_g_object_unref0 (self->info_dialog);
		self->info_dialog = _tmp1_;
		_tmp2_ = self->info_dialog;
		_tmp3_ = self->priv->parent;
		gtk_window_set_transient_for ((GtkWindow*) _tmp2_, _tmp3_);
		_tmp4_ = self->info_dialog;
		_tmp5_ = self->priv->client;
		abraca_medialib_info_dialog_set_client (_tmp4_, _tmp5_);
		_tmp6_ = self->info_dialog;
		g_signal_connect_object ((GtkWidget*) _tmp6_, "delete-event", (GCallback) ____lambda10__gtk_widget_delete_event, self, 0);
		_tmp7_ = self->info_dialog;
		gtk_widget_show_all ((GtkWidget*) _tmp7_);
	}
	_tmp8_ = self->info_dialog;
	_tmp9_ = mid;
	abraca_medialib_info_dialog_add_mid (_tmp8_, _tmp9_);
}
