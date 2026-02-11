tracker_main_config_verbosity_changed_cb (GObject* object, GParamSpec* spec) {
	GObject* _tmp0_;
	gint _tmp1_;
	gint _tmp2_;
	gint verbosity;
	const gchar* _tmp3_ = NULL;
	gint _tmp4_;
	gint _tmp5_;
	const gchar* _tmp6_;
	gint _tmp7_;
#line 146 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	g_return_if_fail (object != NULL);
#line 147 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp0_ = object;
#line 147 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp1_ = tracker_config_get_verbosity (G_TYPE_CHECK_INSTANCE_CAST (_tmp0_, TRACKER_TYPE_CONFIG, TrackerConfig));
#line 147 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp2_ = _tmp1_;
#line 147 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	verbosity = _tmp2_;
#line 151 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp4_ = verbosity;
#line 151 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	if (_tmp4_ > 0) {
#line 151 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
		_tmp3_ = "enabling";
#line 530 "tracker-main.c"
	} else {
#line 151 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
		_tmp3_ = "disabling";
#line 534 "tracker-main.c"
	}
#line 149 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp5_ = verbosity;
#line 149 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp6_ = _tmp3_;
#line 149 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	g_message ("Log verbosity is set to %d, %s D-Bus client lookup", _tmp5_, _tmp6_);
#line 153 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp7_ = verbosity;
#line 153 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	tracker_dbus_enable_client_lookup (_tmp7_ > 0);
#line 546 "tracker-main.c"
}
