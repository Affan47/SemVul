gee_priority_queue_node_pair_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeePriorityQueueType1Node* node1, GeePriorityQueueType1Node* node2) {
	GeePriorityQueueNodePair* self = NULL;
	GeePriorityQueueType1Node* _tmp0_ = NULL;
	GeePriorityQueueType1Node* _tmp1_ = NULL;
	GeePriorityQueueType1Node* _tmp2_ = NULL;
	GeePriorityQueueType1Node* _tmp3_ = NULL;
	g_return_val_if_fail (node1 != NULL, NULL);
	g_return_val_if_fail (node2 != NULL, NULL);
	self = (GeePriorityQueueNodePair*) g_type_create_instance (object_type);
	self->priv->g_type = g_type;
	self->priv->g_dup_func = g_dup_func;
	self->priv->g_destroy_func = g_destroy_func;
	_tmp0_ = node1;
	_tmp1_ = _gee_priority_queue_node_ref0 (_tmp0_);
	_gee_priority_queue_node_unref0 (self->node1);
	self->node1 = _tmp1_;
	_tmp2_ = node2;
	_tmp3_ = _gee_priority_queue_node_ref0 (_tmp2_);
	_gee_priority_queue_node_unref0 (self->node2);
	self->node2 = _tmp3_;
	return self;
}
