mpris2_controller_transport_update (Mpris2Controller* self, TransportAction command) {
	TransportAction _tmp0_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = command;
	if (_tmp0_ == TRANSPORT_ACTION_PLAY_PAUSE) {
		MprisPlayer* _tmp1_ = NULL;
		_tmp1_ = self->priv->_player;
		mpris_player_PlayPause (_tmp1_, NULL, NULL);
	} else {
		TransportAction _tmp2_ = 0;
		_tmp2_ = command;
		if (_tmp2_ == TRANSPORT_ACTION_PREVIOUS) {
			MprisPlayer* _tmp3_ = NULL;
			_tmp3_ = self->priv->_player;
			mpris_player_Previous (_tmp3_, NULL, NULL);
		} else {
			TransportAction _tmp4_ = 0;
			_tmp4_ = command;
			if (_tmp4_ == TRANSPORT_ACTION_NEXT) {
				MprisPlayer* _tmp5_ = NULL;
				_tmp5_ = self->priv->_player;
				mpris_player_Next (_tmp5_, NULL, NULL);
			} else {
				TransportAction _tmp6_ = 0;
				_tmp6_ = command;
				if (_tmp6_ == TRANSPORT_ACTION_REWIND) {
					MprisPlayer* _tmp7_ = NULL;
					_tmp7_ = self->priv->_player;
					mpris_player_Seek (_tmp7_, (gint64) (-500000), NULL, NULL);
				} else {
					TransportAction _tmp8_ = 0;
					_tmp8_ = command;
					if (_tmp8_ == TRANSPORT_ACTION_FORWIND) {
						MprisPlayer* _tmp9_ = NULL;
						_tmp9_ = self->priv->_player;
						mpris_player_Seek (_tmp9_, (gint64) 400000, NULL, NULL);
					}
				}
			}
		}
	}
}
