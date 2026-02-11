gee_array_list_construct (GType object_type, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GeeEqualDataFunc equal_func, void* equal_func_target, GDestroyNotify equal_func_target_destroy_notify) {
	GeeArrayList * self = NULL;
	GeeEqualDataFunc _tmp0_ = NULL;
	void* _tmp0__target = NULL;
	GeeEqualDataFunc _tmp4_ = NULL;
	void* _tmp4__target = NULL;
	gpointer* _tmp5_ = NULL;
	self = (GeeArrayList*) gee_abstract_bidir_list_construct (object_type, g_type, (GBoxedCopyFunc) g_dup_func, g_destroy_func);
	self->priv->g_type = g_type;
	self->priv->g_dup_func = g_dup_func;
	self->priv->g_destroy_func = g_destroy_func;
	_tmp0_ = equal_func;
	_tmp0__target = equal_func_target;
	if (_tmp0_ == NULL) {
		void* _tmp1_ = NULL;
		GDestroyNotify _tmp2_ = NULL;
		GeeEqualDataFunc _tmp3_ = NULL;
		_tmp3_ = gee_functions_get_equal_func_for (g_type, &_tmp1_, &_tmp2_);
		(equal_func_target_destroy_notify == NULL) ? NULL : (equal_func_target_destroy_notify (equal_func_target), NULL);
		equal_func = NULL;
		equal_func_target = NULL;
		equal_func_target_destroy_notify = NULL;
		equal_func = _tmp3_;
		equal_func_target = _tmp1_;
		equal_func_target_destroy_notify = _tmp2_;
	}
	_tmp4_ = equal_func;
	_tmp4__target = equal_func_target;
	gee_array_list_set_equal_func (self, _tmp4_, _tmp4__target);
	_tmp5_ = g_new0 (gpointer, 4);
	self->_items = (_vala_array_free (self->_items, self->_items_length1, (GDestroyNotify) g_destroy_func), NULL);
	self->_items = _tmp5_;
	self->_items_length1 = 4;
	self->__items_size_ = self->_items_length1;
	self->_size = 0;
	(equal_func_target_destroy_notify == NULL) ? NULL : (equal_func_target_destroy_notify (equal_func_target), NULL);
	equal_func = NULL;
	equal_func_target = NULL;
	equal_func_target_destroy_notify = NULL;
	return self;
}
