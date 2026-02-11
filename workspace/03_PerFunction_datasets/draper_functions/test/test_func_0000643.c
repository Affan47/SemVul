tag_data_finalize (TagData* obj) {
	TagData * self;
	GCancellable* _tmp0_;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_TAG_DATA, TagData);
	_tmp0_ = self->cancellable;
	if (_tmp0_ != NULL) {
		GCancellable* _tmp1_;
		_tmp1_ = self->cancellable;
		g_cancellable_cancel (_tmp1_);
		_g_object_unref0 (self->cancellable);
		self->cancellable = NULL;
	}
	_g_object_unref0 (self->tv);
	_g_object_unref0 (self->cancellable);
	_g_free0 (self->tag_id);
}
