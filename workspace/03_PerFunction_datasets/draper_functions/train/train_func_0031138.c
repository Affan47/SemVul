block1_data_unref (Block1Data* _data1_) {
	if (g_atomic_int_dec_and_test (&_data1_->_ref_count_)) {
		_g_object_unref0 (_data1_->self);
		_g_object_unref0 (_data1_->check_all);
		g_slice_free (Block1Data, _data1_);
	}
}
