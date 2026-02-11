preferences_dialog_show_me (MainWindow* parent) {
	PreferencesDialog* _tmp0_ = NULL;
	MainWindow* _tmp3_ = NULL;
	PreferencesDialog* _tmp4_ = NULL;
	GtkWindow* _tmp5_ = NULL;
	PreferencesDialog* _tmp8_ = NULL;
	g_return_if_fail (parent != NULL);
	_tmp0_ = preferences_dialog__instance;
	if (_tmp0_ == NULL) {
		PreferencesDialog* _tmp1_ = NULL;
		PreferencesDialog* _tmp2_ = NULL;
		_tmp1_ = preferences_dialog_new ();
		g_object_ref_sink (_tmp1_);
		_g_object_unref0 (preferences_dialog__instance);
		preferences_dialog__instance = _tmp1_;
		_tmp2_ = preferences_dialog__instance;
		g_signal_connect ((GtkWidget*) _tmp2_, "destroy", (GCallback) ____lambda28__gtk_widget_destroy, NULL);
	}
	_tmp3_ = parent;
	_tmp4_ = preferences_dialog__instance;
	_tmp5_ = gtk_window_get_transient_for ((GtkWindow*) _tmp4_);
	if (G_TYPE_CHECK_INSTANCE_CAST (_tmp3_, GTK_TYPE_WINDOW, GtkWindow) != _tmp5_) {
		PreferencesDialog* _tmp6_ = NULL;
		MainWindow* _tmp7_ = NULL;
		_tmp6_ = preferences_dialog__instance;
		_tmp7_ = parent;
		gtk_window_set_transient_for ((GtkWindow*) _tmp6_, (GtkWindow*) _tmp7_);
	}
	_tmp8_ = preferences_dialog__instance;
	gtk_window_present ((GtkWindow*) _tmp8_);
}
