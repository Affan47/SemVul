unity_inspector_finalize (GObject* obj) {
	UnityInspector * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, UNITY_TYPE_INSPECTOR, UnityInspector);
	_g_free0 (self->priv->_unity_bus_name);
	_g_object_unref0 (self->priv->bus);
	G_OBJECT_CLASS (unity_inspector_parent_class)->finalize (obj);
}
