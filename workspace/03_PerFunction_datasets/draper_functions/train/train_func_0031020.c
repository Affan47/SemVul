unsolicited_response_handler_func_wrapper_finalize (UnsolicitedResponseHandlerFuncWrapper* obj) {
	UnsolicitedResponseHandlerFuncWrapper * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_UNSOLICITED_RESPONSE_HANDLER_FUNC_WRAPPER, UnsolicitedResponseHandlerFuncWrapper);
	(self->func_target_destroy_notify == NULL) ? NULL : (self->func_target_destroy_notify (self->func_target), NULL);
	self->func = NULL;
	self->func_target = NULL;
	self->func_target_destroy_notify = NULL;
}
