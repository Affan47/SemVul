gee_concurrent_list_real_clear (GeeAbstractCollection* base) {
	GeeConcurrentList * self;
	GeeHazardPointerContext* ctx = NULL;
	GeeHazardPointerContext* _tmp0_ = NULL;
	GeeIterator* iter = NULL;
	GeeIterator* _tmp1_ = NULL;
	GeeConcurrentListNode* _tmp5_ = NULL;
	GeeConcurrentListNode* _tmp6_ = NULL;
	self = (GeeConcurrentList*) base;
	_tmp0_ = gee_hazard_pointer_context_new (NULL);
	ctx = _tmp0_;
	_tmp1_ = gee_abstract_collection_iterator ((GeeAbstractCollection*) self);
	iter = _tmp1_;
	while (TRUE) {
		GeeIterator* _tmp2_ = NULL;
		gboolean _tmp3_ = FALSE;
		GeeIterator* _tmp4_ = NULL;
		_tmp2_ = iter;
		_tmp3_ = gee_iterator_next (_tmp2_);
		if (!_tmp3_) {
			break;
		}
		_tmp4_ = iter;
		gee_iterator_remove (_tmp4_);
	}
	_tmp5_ = self->priv->_head;
	_tmp6_ = _gee_concurrent_list_node_ref0 (_tmp5_);
	gee_hazard_pointer_set_pointer (GEE_CONCURRENT_LIST_TYPE_NODE, (GBoxedCopyFunc) gee_concurrent_list_node_ref, gee_concurrent_list_node_unref, &self->priv->_tail, _tmp6_, (gsize) 0, (gsize) 0);
	_g_object_unref0 (iter);
	_gee_hazard_pointer_context_free0 (ctx);
}
