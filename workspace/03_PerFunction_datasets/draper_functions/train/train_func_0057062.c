fso_framework_test_signal_wrapper_setup (FsoFrameworkTestSignalWrapper* self) {
	GObject* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gulong _tmp2_ = 0UL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_emitter;
	_tmp1_ = self->priv->_signame;
	_tmp2_ = g_signal_connect_swapped (_tmp0_, _tmp1_, (GCallback) fso_framework_test_signal_wrapper_callback, self);
	fso_framework_test_signal_wrapper_set_id (self, _tmp2_);
	fso_framework_test_signal_wrapper_set_catch_count (self, 0);
}
