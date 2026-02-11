unity_mpris_player_get_can_pause (UnityMprisPlayer* self) {
	gboolean result;
	UnityMusicPlayer* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->priv->consumer;
	_tmp1_ = unity_music_player_get_can_pause (_tmp0_);
	_tmp2_ = _tmp1_;
	result = _tmp2_;
	return result;
}
