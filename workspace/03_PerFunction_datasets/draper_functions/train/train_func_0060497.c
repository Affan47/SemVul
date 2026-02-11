post_processor_get_detailed_messages (PostProcessor* self) {
	GeeList* result = NULL;
	GeeList* _tmp0_ = NULL;
	GeeList* _tmp1_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->_all_messages;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	result = _tmp1_;
	return result;
}
