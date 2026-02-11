caribou_row_model_real_get_children (CaribouIKeyboardObject* base, int* result_length1) {
	CaribouRowModel * self;
	CaribouIKeyboardObject** result = NULL;
	gint _tmp0_ = 0;
	CaribouColumnModel** _tmp1_ = NULL;
	CaribouIKeyboardObject** _tmp2_ = NULL;
	gint _tmp2__length1 = 0;
	self = (CaribouRowModel*) base;
	_tmp1_ = caribou_row_model_get_columns (self, &_tmp0_);
	_tmp2_ = (CaribouIKeyboardObject**) _tmp1_;
	_tmp2__length1 = (_tmp0_ * sizeof (CaribouColumnModel*)) / sizeof (CaribouIKeyboardObject*);
	if (result_length1) {
		*result_length1 = _tmp2__length1;
	}
	result = _tmp2_;
	return result;
}
