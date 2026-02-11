dvb_player_thread_set_playing_or_destroy (DVBPlayerThread* self) {
	gboolean result = FALSE;
	GstStateChangeReturn ret = 0;
	GstElement* _tmp0_ = NULL;
	GstStateChangeReturn _tmp1_ = 0;
	GstStateChangeReturn _tmp2_ = 0;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->priv->pipeline;
	_tmp1_ = gst_element_set_state (_tmp0_, GST_STATE_PLAYING);
	ret = _tmp1_;
	_tmp2_ = ret;
	if (_tmp2_ == GST_STATE_CHANGE_FAILURE) {
		DVBLoggingLogger* _tmp3_ = NULL;
		_tmp3_ = dvb_player_thread_log;
		dvb_logging_logger_error (_tmp3_, "ChannelFactory.vala:379: Failed setting pipeline to playing");
		dvb_player_thread_destroy (self, FALSE);
		result = FALSE;
		return result;
	}
	result = TRUE;
	return result;
}
