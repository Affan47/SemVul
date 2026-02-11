gee_concurrent_list_iterator_real_set (GeeListIterator* base, gconstpointer item) {
	GeeConcurrentListIterator * self;
	GeeHazardPointerContext* ctx = NULL;
	GeeHazardPointerContext* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	GeeConcurrentListNode* _tmp3_ = NULL;
	gconstpointer _tmp4_ = NULL;
	gpointer _tmp5_ = NULL;
	self = (GeeConcurrentListIterator*) base;
	_tmp0_ = gee_hazard_pointer_context_new (NULL);
	ctx = _tmp0_;
	_tmp1_ = gee_iterator_get_valid ((GeeIterator*) self);
	_tmp2_ = _tmp1_;
	_vala_assert (_tmp2_, "valid");
	_tmp3_ = self->priv->_curr;
	_tmp4_ = item;
	_tmp5_ = ((_tmp4_ != NULL) && (self->priv->g_dup_func != NULL)) ? self->priv->g_dup_func ((gpointer) _tmp4_) : ((gpointer) _tmp4_);
	gee_hazard_pointer_set_pointer (self->priv->g_type, (GBoxedCopyFunc) self->priv->g_dup_func, self->priv->g_destroy_func, &_tmp3_->_data, _tmp5_, (gsize) 0, (gsize) 0);
	_gee_hazard_pointer_context_free0 (ctx);
}
