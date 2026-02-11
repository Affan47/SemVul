fso_framework_abstract_command_queue_checkRestartingQ (FsoFrameworkAbstractCommandQueue* self) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	FsoFrameworkAbstractCommandHandler* _tmp1_ = NULL;
	gboolean _tmp5_ = FALSE;
	GeeLinkedList* _tmp6_ = NULL;
	gint _tmp7_ = 0;
	gint _tmp8_ = 0;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp1_ = self->current;
	if (_tmp1_ == NULL) {
		GeeLinkedList* _tmp2_ = NULL;
		gint _tmp3_ = 0;
		gint _tmp4_ = 0;
		_tmp2_ = self->priv->q;
		_tmp3_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp2_);
		_tmp4_ = _tmp3_;
		_tmp0_ = _tmp4_ > 0;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp5_ = _tmp0_;
	if (_tmp5_) {
		fso_framework_abstract_command_queue_writeNextCommand (self);
	}
	_tmp6_ = self->priv->q;
	_tmp7_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp6_);
	_tmp8_ = _tmp7_;
	result = _tmp8_ > 0;
	return result;
}
