_vala_gee_abstract_map_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GeeAbstractMap * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, GEE_TYPE_ABSTRACT_MAP, GeeAbstractMap);
	switch (property_id) {
		case GEE_ABSTRACT_MAP_IS_EMPTY:
		g_value_set_boolean (value, gee_abstract_map_get_is_empty (self));
		break;
		case GEE_ABSTRACT_MAP_READ_ONLY_VIEW:
		g_value_take_object (value, gee_abstract_map_get_read_only_view (self));
		break;
		case GEE_ABSTRACT_MAP_KEY_TYPE:
		g_value_set_gtype (value, gee_map_get_key_type ((GeeMap*) self));
		break;
		case GEE_ABSTRACT_MAP_VALUE_TYPE:
		g_value_set_gtype (value, gee_map_get_value_type ((GeeMap*) self));
		break;
		case GEE_ABSTRACT_MAP_ELEMENT_TYPE:
		g_value_set_gtype (value, gee_iterable_get_element_type ((GeeIterable*) self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
