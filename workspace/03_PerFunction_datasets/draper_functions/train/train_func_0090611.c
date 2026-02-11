abraca_client_set_playlist_id (AbracaClient* self, gint mid) {
	gint _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_current_playback_status;
	if (_tmp0_ == ((gint) XMMS_PLAYBACK_STATUS_STOP)) {
		gint _tmp1_;
		_tmp1_ = mid;
		g_signal_emit_by_name (self, "playback-current-id", _tmp1_);
	}
}
