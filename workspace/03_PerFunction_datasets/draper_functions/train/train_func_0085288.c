tracker_dbus_register_prepare_class_signal (void) {
	gboolean result = FALSE;
	TrackerResources* _tmp0_ = NULL;
	TrackerResources* _tmp1_ = NULL;
#line 229 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	_tmp0_ = tracker_dbus_resources;
#line 229 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	if (_tmp0_ == NULL) {
#line 230 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		g_message ("Error during initialization, Resources DBus object not available");
#line 231 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		result = FALSE;
#line 231 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		return result;
#line 939 "tracker-dbus.c"
	}
#line 234 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	_tmp1_ = tracker_dbus_resources;
#line 234 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	tracker_resources_enable_signals (_tmp1_);
#line 236 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	result = TRUE;
#line 236 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	return result;
#line 949 "tracker-dbus.c"
}
