chess_engine_cecp_real_report_move (ChessEngine* base, ChessMove* move) {
	ChessEngineCECP * self;
	gboolean _tmp0_;
	self = (ChessEngineCECP*) base;
	g_return_if_fail (move != NULL);
	_tmp0_ = self->priv->moving;
	if (!_tmp0_) {
		ChessMove* _tmp1_;
		gchar* _tmp2_ = NULL;
		gchar* _tmp3_;
		chess_engine_write_line ((ChessEngine*) self, "force");
		_tmp1_ = move;
		_tmp2_ = chess_move_get_engine (_tmp1_);
		_tmp3_ = _tmp2_;
		chess_engine_write_line ((ChessEngine*) self, _tmp3_);
		_g_free0 (_tmp3_);
	}
	self->priv->moving = FALSE;
}
