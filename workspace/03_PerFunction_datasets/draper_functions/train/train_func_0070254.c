zeitgeist_monitor_manager_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	ZeitgeistMonitorManager * self;
	GHashFunc _tmp0_ = NULL;
	GEqualFunc _tmp1_ = NULL;
	GHashTable* _tmp2_ = NULL;
	GHashFunc _tmp3_ = NULL;
	GEqualFunc _tmp4_ = NULL;
	GHashTable* _tmp5_ = NULL;
	GError * _inner_error_ = NULL;
	parent_class = G_OBJECT_CLASS (zeitgeist_monitor_manager_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, ZEITGEIST_TYPE_MONITOR_MANAGER, ZeitgeistMonitorManager);
	zeitgeist_monitor_manager_instance = self;
	_tmp0_ = g_str_hash;
	_tmp1_ = g_str_equal;
	_tmp2_ = g_hash_table_new_full (_tmp0_, _tmp1_, _g_free0_, _zeitgeist_monitor_manager_monitor_unref0_);
	_g_hash_table_unref0 (self->priv->monitors);
	self->priv->monitors = _tmp2_;
	_tmp3_ = g_str_hash;
	_tmp4_ = g_str_equal;
	_tmp5_ = g_hash_table_new_full (_tmp3_, _tmp4_, _g_free0_, _g_ptr_array_unref0_);
	_g_hash_table_unref0 (self->priv->connections);
	self->priv->connections = _tmp5_;
	{
		GDBusConnection* connection = NULL;
		GDBusConnection* _tmp6_ = NULL;
		GDBusConnection* _tmp7_ = NULL;
		_tmp6_ = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, &_inner_error_);
		connection = _tmp6_;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_IO_ERROR) {
				goto __catch7_g_io_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
		}
		_tmp7_ = connection;
		g_dbus_connection_signal_subscribe (_tmp7_, "org.freedesktop.DBus", "org.freedesktop.DBus", "NameOwnerChanged", "/org/freedesktop/DBus", NULL, 0, __zeitgeist_monitor_manager____lambda5__gd_bus_signal_callback, g_object_ref (self), g_object_unref);
		_g_object_unref0 (connection);
	}
	goto __finally7;
	__catch7_g_io_error:
	{
		GError* err = NULL;
		GError* _tmp8_ = NULL;
		const gchar* _tmp9_ = NULL;
		err = _inner_error_;
		_inner_error_ = NULL;
		_tmp8_ = err;
		_tmp9_ = _tmp8_->message;
		g_warning ("notify.vala:91: Cannot subscribe to NameOwnerChanged signal! %s", _tmp9_);
		_g_error_free0 (err);
	}
	__finally7:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
	}
	return obj;
}
