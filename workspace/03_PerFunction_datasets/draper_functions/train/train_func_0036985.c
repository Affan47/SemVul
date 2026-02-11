block8_data_unref (void * _userdata_) {
	Block8Data* _data8_;
	_data8_ = (Block8Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data8_->_ref_count_)) {
		NokiaIsiIsiNetworkGetStatus * self;
		self = _data8_->self;
		gisi_comm_network_isi_regstatus_destroy (&_data8_->istatus);
		_g_object_unref0 (self);
		g_slice_free (Block8Data, _data8_);
	}
}
