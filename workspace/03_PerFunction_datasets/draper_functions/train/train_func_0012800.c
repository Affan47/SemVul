gee_tim_sort_slice_pop_last (GeeTimSortSlice* self) {
	void* result = NULL;
	gint _tmp0_ = 0;
	void** _tmp1_ = NULL;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	void* _tmp4_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->length;
	self->length = _tmp0_ - 1;
	_tmp1_ = self->list;
	_tmp2_ = self->index;
	_tmp3_ = self->length;
	_tmp4_ = _tmp1_[_tmp2_ + _tmp3_];
	result = _tmp4_;
	return result;
}
