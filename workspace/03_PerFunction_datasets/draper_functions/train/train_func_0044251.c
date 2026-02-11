unity_inspector_on_unity_appeared (UnityInspector* self, GDBusConnection* conn, const gchar* name, const gchar* name_owner) {
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (conn != NULL);
	g_return_if_fail (name != NULL);
	g_return_if_fail (name_owner != NULL);
	_tmp0_ = name;
	if (g_strcmp0 (_tmp0_, "com.canonical.Unity") != 0) {
		const gchar* _tmp1_ = NULL;
		_tmp1_ = name;
		g_critical ("Internal error in libunity: Got name owner notification " "from '%s'. Expected 'com.canonical.Unity'", _tmp1_);
		return;
	}
	self->priv->_unity_running = TRUE;
	_tmp2_ = name_owner;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 (self->priv->_unity_bus_name);
	self->priv->_unity_bus_name = _tmp3_;
	g_object_notify ((GObject*) self, "unity-running");
	g_object_notify ((GObject*) self, "unity-bus-name");
}
