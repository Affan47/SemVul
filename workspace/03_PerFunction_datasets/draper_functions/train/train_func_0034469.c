gee_tree_set_find_ceil (GeeTreeSet* self, gconstpointer item) {
	GeeTreeSetNode* result = NULL;
	GeeTreeSetNode* node = NULL;
	gconstpointer _tmp0_ = NULL;
	GeeTreeSetNode* _tmp1_ = NULL;
	GeeTreeSetNode* _tmp2_ = NULL;
	GeeTreeSetNode* _tmp3_ = NULL;
	GCompareFunc _tmp4_ = NULL;
	GCompareFunc _tmp5_ = NULL;
	gconstpointer _tmp6_ = NULL;
	GeeTreeSetNode* _tmp7_ = NULL;
	gconstpointer _tmp8_ = NULL;
	gint _tmp9_ = 0;
	GeeTreeSetNode* _tmp13_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = item;
	_tmp1_ = gee_tree_set_find_nearest (self, _tmp0_);
	node = _tmp1_;
	_tmp2_ = node;
	if (_tmp2_ == NULL) {
		result = NULL;
		return result;
	}
	_tmp4_ = gee_tree_set_get_compare_func (self);
	_tmp5_ = _tmp4_;
	_tmp6_ = item;
	_tmp7_ = node;
	_tmp8_ = _tmp7_->key;
	_tmp9_ = _tmp5_ (_tmp6_, _tmp8_);
	if (_tmp9_ > 0) {
		GeeTreeSetNode* _tmp10_ = NULL;
		GeeTreeSetNode* _tmp11_ = NULL;
		_tmp10_ = node;
		_tmp11_ = _tmp10_->next;
		_tmp3_ = _tmp11_;
	} else {
		GeeTreeSetNode* _tmp12_ = NULL;
		_tmp12_ = node;
		_tmp3_ = _tmp12_;
	}
	_tmp13_ = _tmp3_;
	result = _tmp13_;
	return result;
}
