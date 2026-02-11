block1_data_unref (void * _userdata_) {
	Block1Data* _data1_;
	_data1_ = (Block1Data*) _userdata_;
#line 61 "/home/treitter/collabora/folks/tests/eds/helper-prepare-aggregator.vala"
	if (g_atomic_int_dec_and_test (&_data1_->_ref_count_)) {
#line 61 "/home/treitter/collabora/folks/tests/eds/helper-prepare-aggregator.vala"
		_g_object_unref0 (_data1_->_result_);
#line 61 "/home/treitter/collabora/folks/tests/eds/helper-prepare-aggregator.vala"
		_g_main_loop_unref0 (_data1_->loop);
#line 61 "/home/treitter/collabora/folks/tests/eds/helper-prepare-aggregator.vala"
		g_slice_free (Block1Data, _data1_);
#line 236 "helper-prepare-aggregator.c"
	}
}
