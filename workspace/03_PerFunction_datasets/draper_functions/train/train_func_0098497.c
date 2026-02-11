fso_framework_abstract_command_queue_onHupFromTransport (FsoFrameworkAbstractCommandQueue* self) {
	FsoFrameworkTransport* _tmp0_ = NULL;
	FsoFrameworkTransport* _tmp1_ = NULL;
	FsoFrameworkLogger* _tmp2_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = fso_framework_command_queue_get_transport ((FsoFrameworkCommandQueue*) self);
	_tmp1_ = _tmp0_;
	_tmp2_ = _tmp1_->logger;
	fso_framework_logger_warning (_tmp2_, "HUP from transport; signalling to upper layer");
	g_signal_emit_by_name (self, "hangup");
}
