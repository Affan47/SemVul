fso_framework_threading_dummy_thread_main (FsoFrameworkThreadingDummyThread* self) {
	void* result = NULL;
	FsoFrameworkThreadingVoidFuncWithVoidStarParam _tmp0_ = NULL;
	void* _tmp0__target = NULL;
	FsoFrameworkThreadingVoidFuncWithVoidStarParam _tmp1_ = NULL;
	void* _tmp1__target = NULL;
	void* _tmp2_ = NULL;
	FsoFrameworkThreadingDummyThread* _tmp3_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_vala_assert (self != NULL, "this != null");
	_tmp0_ = self->priv->func;
	_tmp0__target = self->priv->func_target;
	_vala_assert (_tmp0_ != NULL, "func != null");
	_tmp1_ = self->priv->func;
	_tmp1__target = self->priv->func_target;
	_tmp2_ = self->priv->param;
	_tmp1_ (_tmp2_, _tmp1__target);
	_tmp3_ = self->pself;
	fso_framework_threading_dummy_thread_unref (_tmp3_);
	result = NULL;
	return result;
}
