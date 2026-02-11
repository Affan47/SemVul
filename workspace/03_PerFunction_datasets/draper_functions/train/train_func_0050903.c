block11_data_unref (void * _userdata_) {
	Block11Data* _data11_;
	_data11_ = (Block11Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data11_->_ref_count_)) {
		GeeTraversable * self;
		GType a_type;
		GBoxedCopyFunc a_dup_func;
		GDestroyNotify a_destroy_func;
		self = _data11_->self;
		a_type = _data11_->a_type;
		a_dup_func = _data11_->a_dup_func;
		a_destroy_func = _data11_->a_destroy_func;
		_g_object_unref0 (self);
		g_slice_free (Block11Data, _data11_);
	}
}
