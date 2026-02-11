_vala_gee_concurrent_set_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	GeeConcurrentSet * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, GEE_TYPE_CONCURRENT_SET, GeeConcurrentSet);
	switch (property_id) {
		case GEE_CONCURRENT_SET_G_TYPE:
		self->priv->g_type = g_value_get_gtype (value);
		break;
		case GEE_CONCURRENT_SET_G_DUP_FUNC:
		self->priv->g_dup_func = g_value_get_pointer (value);
		break;
		case GEE_CONCURRENT_SET_G_DESTROY_FUNC:
		self->priv->g_destroy_func = g_value_get_pointer (value);
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
