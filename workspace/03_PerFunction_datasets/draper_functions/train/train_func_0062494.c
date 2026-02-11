unity_category_finalize (GObject* obj) {
	UnityCategory * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, UNITY_TYPE_CATEGORY, UnityCategory);
	_g_free0 (self->priv->_id);
	_g_free0 (self->priv->_name);
	_g_object_unref0 (self->priv->_icon_hint);
	_g_free0 (self->priv->_renderer_hint);
	_g_hash_table_unref0 (self->priv->hints);
	G_OBJECT_CLASS (unity_category_parent_class)->finalize (obj);
}
