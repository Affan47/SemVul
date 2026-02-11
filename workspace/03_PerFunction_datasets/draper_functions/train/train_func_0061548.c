_vala_gee_hash_map_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GeeHashMap * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, GEE_TYPE_HASH_MAP, GeeHashMap);
	switch (property_id) {
		case GEE_HASH_MAP_SIZE:
		g_value_set_int (value, gee_abstract_map_get_size ((GeeAbstractMap*) self));
		break;
		case GEE_HASH_MAP_READ_ONLY:
		g_value_set_boolean (value, gee_abstract_map_get_read_only ((GeeAbstractMap*) self));
		break;
		case GEE_HASH_MAP_KEYS:
		g_value_take_object (value, gee_abstract_map_get_keys ((GeeAbstractMap*) self));
		break;
		case GEE_HASH_MAP_VALUES:
		g_value_take_object (value, gee_abstract_map_get_values ((GeeAbstractMap*) self));
		break;
		case GEE_HASH_MAP_ENTRIES:
		g_value_take_object (value, gee_abstract_map_get_entries ((GeeAbstractMap*) self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
