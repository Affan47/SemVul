_vala_gee_read_only_collection_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GeeReadOnlyCollection * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, GEE_TYPE_READ_ONLY_COLLECTION, GeeReadOnlyCollection);
	switch (property_id) {
		case GEE_READ_ONLY_COLLECTION_SIZE:
		g_value_set_int (value, gee_collection_get_size ((GeeCollection*) self));
		break;
		case GEE_READ_ONLY_COLLECTION_IS_EMPTY:
		g_value_set_boolean (value, gee_collection_get_is_empty ((GeeCollection*) self));
		break;
		case GEE_READ_ONLY_COLLECTION_ELEMENT_TYPE:
		g_value_set_gtype (value, gee_iterable_get_element_type ((GeeIterable*) self));
		break;
		case GEE_READ_ONLY_COLLECTION_READ_ONLY_VIEW:
		g_value_take_object (value, gee_read_only_collection_get_read_only_view (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
