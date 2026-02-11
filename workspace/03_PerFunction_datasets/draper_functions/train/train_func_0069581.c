tracker_stats_setup_dbus (TrackerStats* self) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_debug ("tracker-stats.vala:43: Setting up statistics D-Bus connection");
	{
		Statistics* _tmp0_ = NULL;
		Statistics* _tmp1_;
		_tmp0_ = g_initable_new (TYPE_STATISTICS_PROXY, NULL, &_inner_error_, "g-flags", G_DBUS_PROXY_FLAGS_DO_NOT_LOAD_PROPERTIES | G_DBUS_PROXY_FLAGS_DO_NOT_CONNECT_SIGNALS, "g-name", "org.freedesktop.Tracker1", "g-bus-type", G_BUS_TYPE_SESSION, "g-object-path", "/org/freedesktop/Tracker1/Statistics", "g-interface-name", "org.freedesktop.Tracker1.Statistics", NULL);
		_tmp1_ = (Statistics*) _tmp0_;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_IO_ERROR) {
				goto __catch11_g_io_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
		_g_object_unref0 (self->priv->tracker);
		self->priv->tracker = _tmp1_;
	}
	goto __finally11;
	__catch11_g_io_error:
	{
		GError* e = NULL;
		GError* _tmp2_;
		const gchar* _tmp3_;
		GtkMessageDialog* _tmp4_;
		GtkMessageDialog* msg;
		GtkMessageDialog* _tmp5_;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp2_ = e;
		_tmp3_ = _tmp2_->message;
		_tmp4_ = (GtkMessageDialog*) gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CANCEL, "Error connecting to D-Bus session bus, %s", _tmp3_);
		g_object_ref_sink (_tmp4_);
		msg = _tmp4_;
		_tmp5_ = msg;
		gtk_dialog_run ((GtkDialog*) _tmp5_);
		gtk_main_quit ();
		_g_object_unref0 (msg);
		_g_error_free0 (e);
	}
	__finally11:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}
