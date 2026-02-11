_vala_gee_priority_queue_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GeePriorityQueue * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, GEE_TYPE_PRIORITY_QUEUE, GeePriorityQueue);
	switch (property_id) {
		case GEE_PRIORITY_QUEUE_COMPARE_FUNC:
		g_value_set_pointer (value, gee_priority_queue_get_compare_func (self));
		break;
		case GEE_PRIORITY_QUEUE_CAPACITY:
		g_value_set_int (value, gee_abstract_queue_get_capacity ((GeeAbstractQueue*) self));
		break;
		case GEE_PRIORITY_QUEUE_REMAINING_CAPACITY:
		g_value_set_int (value, gee_abstract_queue_get_remaining_capacity ((GeeAbstractQueue*) self));
		break;
		case GEE_PRIORITY_QUEUE_IS_FULL:
		g_value_set_boolean (value, gee_abstract_queue_get_is_full ((GeeAbstractQueue*) self));
		break;
		case GEE_PRIORITY_QUEUE_SIZE:
		g_value_set_int (value, gee_abstract_collection_get_size ((GeeAbstractCollection*) self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
