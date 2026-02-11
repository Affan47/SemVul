dvb_channel_list_load (DVBChannelList* self, DVBAdapterType type, GError** error) {
	DVBioChannelListReader* reader = NULL;
	DVBAdapterType _tmp0_ = 0;
	DVBioChannelListReader* _tmp1_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = type;
	_tmp1_ = dvb_io_channel_list_reader_new (self, _tmp0_);
	reader = _tmp1_;
	dvb_io_channel_list_reader_read_into (reader, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_g_object_unref0 (reader);
		return;
	}
	_g_object_unref0 (reader);
}
