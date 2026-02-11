gee_concurrent_list_node_set_succ (GeeConcurrentListNode* self, GeeConcurrentListNode* next, GeeConcurrentListState state) {
	GeeConcurrentListNode* _tmp0_ = NULL;
	GeeConcurrentListNode* _tmp1_ = NULL;
	GeeConcurrentListState _tmp2_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = next;
	_tmp1_ = _gee_concurrent_list_node_ref0 (_tmp0_);
	_tmp2_ = state;
	gee_hazard_pointer_set_pointer (GEE_CONCURRENT_LIST_TYPE_NODE, (GBoxedCopyFunc) gee_concurrent_list_node_ref, gee_concurrent_list_node_unref, &self->_succ, _tmp1_, (gsize) 3, (gsize) _tmp2_);
}
