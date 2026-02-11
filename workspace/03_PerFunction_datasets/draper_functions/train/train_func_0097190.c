gee_concurrent_list_node_set_backlink (GeeConcurrentListNode* self, GeeConcurrentListNode* backlink) {
	GeeConcurrentListNode* _tmp0_ = NULL;
	GeeConcurrentListNode* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = backlink;
	_tmp1_ = _gee_concurrent_list_node_ref0 (_tmp0_);
	gee_hazard_pointer_compare_and_exchange_pointer (GEE_CONCURRENT_LIST_TYPE_NODE, (GBoxedCopyFunc) gee_concurrent_list_node_ref, gee_concurrent_list_node_unref, &self->_backlink, NULL, _tmp1_, (gsize) 0, (gsize) 0, (gsize) 0);
}
