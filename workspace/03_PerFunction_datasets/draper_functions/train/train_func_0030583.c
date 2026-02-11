chess_engine_uci_real_report_move (ChessEngine* base, ChessMove* move) {
	ChessEngineUCI * self;
	const gchar* _tmp0_;
	ChessMove* _tmp1_;
	gchar* _tmp2_ = NULL;
	gchar* _tmp3_;
	gchar* _tmp4_;
	gchar* _tmp5_;
	gchar* _tmp6_;
	self = (ChessEngineUCI*) base;
	g_return_if_fail (move != NULL);
	_tmp0_ = self->priv->moves;
	_tmp1_ = move;
	_tmp2_ = chess_move_get_engine (_tmp1_);
	_tmp3_ = _tmp2_;
	_tmp4_ = g_strconcat (" ", _tmp3_, NULL);
	_tmp5_ = _tmp4_;
	_tmp6_ = g_strconcat (_tmp0_, _tmp5_, NULL);
	_g_free0 (self->priv->moves);
	self->priv->moves = _tmp6_;
	_g_free0 (_tmp5_);
	_g_free0 (_tmp3_);
}
