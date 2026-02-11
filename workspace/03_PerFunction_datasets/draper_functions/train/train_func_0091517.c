tracker_dbus_init (void) {
	gboolean result = FALSE;
	GDBusConnection* _tmp0_ = NULL;
	GError * _inner_error_ = NULL;
#line 90 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	_tmp0_ = tracker_dbus_connection;
#line 90 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	if (_tmp0_ != NULL) {
#line 91 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		result = TRUE;
#line 91 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		return result;
#line 442 "tracker-dbus.c"
	}
	{
		GDBusConnection* _tmp1_ = NULL;
		GDBusConnection* _tmp2_ = NULL;
#line 95 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		_tmp2_ = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, &_inner_error_);
#line 95 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		_tmp1_ = _tmp2_;
#line 95 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		if (_inner_error_ != NULL) {
#line 453 "tracker-dbus.c"
			goto __catch4_g_error;
		}
#line 95 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		_g_object_unref0 (tracker_dbus_connection);
#line 95 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		tracker_dbus_connection = _tmp1_;
#line 460 "tracker-dbus.c"
	}
	goto __finally4;
	__catch4_g_error:
	{
		GError* e = NULL;
		GError* _tmp3_ = NULL;
		const gchar* _tmp4_ = NULL;
#line 94 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		e = _inner_error_;
#line 94 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		_inner_error_ = NULL;
#line 97 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		_tmp3_ = e;
#line 97 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		_tmp4_ = _tmp3_->message;
#line 97 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		g_critical ("Could not connect to the D-Bus session bus, %s", _tmp4_);
#line 98 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		result = FALSE;
#line 98 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		_g_error_free0 (e);
#line 98 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		return result;
#line 484 "tracker-dbus.c"
	}
	__finally4:
#line 94 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	if (_inner_error_ != NULL) {
#line 94 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 94 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		g_clear_error (&_inner_error_);
#line 94 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
		return FALSE;
#line 495 "tracker-dbus.c"
	}
#line 101 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	result = TRUE;
#line 101 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-dbus.vala"
	return result;
#line 501 "tracker-dbus.c"
}
