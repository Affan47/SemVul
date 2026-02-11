zeitgeist_daemon_name_lost_callback (GDBusConnection* conn) {
	GDBusConnection* _tmp0_ = NULL;
	_tmp0_ = conn;
	if (_tmp0_ == NULL) {
		GMainLoop* _tmp1_ = NULL;
		_tmp1_ = zeitgeist_daemon_mainloop;
		g_main_loop_quit (_tmp1_);
	} else {
		gboolean _tmp2_ = FALSE;
		ZeitgeistDaemon* _tmp3_ = NULL;
		gboolean _tmp5_ = FALSE;
		_tmp3_ = zeitgeist_daemon_instance;
		if (_tmp3_ != NULL) {
			gboolean _tmp4_ = FALSE;
			_tmp4_ = zeitgeist_daemon_name_acquired;
			_tmp2_ = !_tmp4_;
		} else {
			_tmp2_ = FALSE;
		}
		_tmp5_ = _tmp2_;
		if (_tmp5_) {
			gboolean _tmp6_ = FALSE;
			_tmp6_ = zeitgeist_daemon_replace_mode;
			if (!_tmp6_) {
			}
			g_debug ("zeitgeist-daemon.vala:348: Waiting 10 seconds to acquire name...");
			g_timeout_add_full (G_PRIORITY_DEFAULT, (guint) 10000, _____lambda2__gsource_func, NULL, NULL);
		} else {
			gboolean _tmp7_ = FALSE;
			ZeitgeistDaemon* _tmp8_ = NULL;
			gboolean _tmp10_ = FALSE;
			_tmp8_ = zeitgeist_daemon_instance;
			if (_tmp8_ != NULL) {
				gboolean _tmp9_ = FALSE;
				_tmp9_ = zeitgeist_daemon_name_acquired;
				_tmp7_ = _tmp9_;
			} else {
				_tmp7_ = FALSE;
			}
			_tmp10_ = _tmp7_;
			if (_tmp10_) {
				GMainLoop* _tmp11_ = NULL;
				_tmp11_ = zeitgeist_daemon_mainloop;
				g_main_loop_quit (_tmp11_);
			}
		}
	}
}
