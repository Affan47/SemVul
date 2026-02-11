resign_cb (GtkWidget* widget, Application* self) {
	ChessGame* _tmp0_;
	ChessPlayer* _tmp1_;
	ChessPlayer* _tmp2_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (widget != NULL);
	_tmp0_ = self->priv->game;
	_tmp1_ = chess_game_get_current_player (_tmp0_);
	_tmp2_ = _tmp1_;
	chess_player_resign (_tmp2_);
}
