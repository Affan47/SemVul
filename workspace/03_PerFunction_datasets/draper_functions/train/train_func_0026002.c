__lambda19_ (Block8Data* _data8_, GIsiCommErrorCode _error_, GIsiCommNetworkISI_RegStatus* isistatus) {
	NokiaIsiIsiNetworkGetStatus * self;
	GIsiCommErrorCode _tmp0_ = 0;
	self = _data8_->self;
	_tmp0_ = _error_;
	if (_tmp0_ == GISI_COMM_ERROR_CODE_OK) {
		GIsiCommNetworkISI_RegStatus* _tmp1_ = NULL;
		GIsiCommNetworkISI_RegStatus _tmp2_ = {0};
		_tmp1_ = isistatus;
		gisi_comm_network_isi_regstatus_copy (_tmp1_, &_tmp2_);
		gisi_comm_network_isi_regstatus_destroy (&_data8_->istatus);
		_data8_->istatus = _tmp2_;
	}
	nokia_isi_isi_network_get_status_real_run_co (_data8_->_async_data_);
}
