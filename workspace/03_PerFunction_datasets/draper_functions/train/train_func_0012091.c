build_tool_runner_abort (BuildToolRunner* self) {
	BuildJobRunner* _tmp0_ = NULL;
	BuildView* _tmp2_ = NULL;
	GtkTreeIter _tmp3_ = {0};
	GtkTreeIter* _tmp4_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_current_job_runner;
	if (_tmp0_ != NULL) {
		BuildJobRunner* _tmp1_ = NULL;
		_tmp1_ = self->priv->_current_job_runner;
		build_job_runner_abort (_tmp1_);
	}
	_tmp2_ = self->priv->_view;
	_tmp3_ = self->priv->_main_title;
	build_view_set_title_state (_tmp2_, &_tmp3_, BUILD_STATE_ABORTED);
	_tmp4_ = self->priv->_current_job_title;
	if (_tmp4_ != NULL) {
		BuildView* _tmp5_ = NULL;
		GtkTreeIter* _tmp6_ = NULL;
		GtkTreeIter _tmp7_ = {0};
		_tmp5_ = self->priv->_view;
		_tmp6_ = self->priv->_current_job_title;
		_tmp7_ = *_tmp6_;
		build_view_set_title_state (_tmp5_, &_tmp7_, BUILD_STATE_ABORTED);
	}
	self->priv->_aborted = TRUE;
	g_signal_emit_by_name (self, "finished");
}
