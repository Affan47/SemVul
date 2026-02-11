dvb_recorder_real_iterator (GeeIterable* base) {
	DVBRecorder * self;
	GeeIterator* result = NULL;
	GeeHashMap* _tmp0_ = NULL;
	GeeCollection* _tmp1_ = NULL;
	GeeCollection* _tmp2_ = NULL;
	GeeCollection* _tmp3_ = NULL;
	GeeIterator* _tmp4_ = NULL;
	GeeIterator* _tmp5_ = NULL;
	self = (DVBRecorder*) base;
	_tmp0_ = self->priv->timers;
	_tmp1_ = gee_abstract_map_get_values ((GeeMap*) _tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = _tmp2_;
	_tmp4_ = gee_iterable_iterator ((GeeIterable*) _tmp3_);
	_tmp5_ = _tmp4_;
	_g_object_unref0 (_tmp3_);
	result = _tmp5_;
	return result;
}
