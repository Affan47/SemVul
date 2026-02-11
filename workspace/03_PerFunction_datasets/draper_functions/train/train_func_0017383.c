___lambda10_ (Block3Data* _data3_) {
	Block2Data* _data2_;
	EdsfPersonaStore * self;
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	_data2_ = _data3_->_data2_;
	self = _data2_->self;
	_tmp0_ = _data3_->has_yielded;
	if (_tmp0_ == TRUE) {
		_edsf_persona_store_commit_modified_property_co (_data2_->_async_data_);
	}
	result = FALSE;
	return result;
}
