chess_game_undo_cb (ChessGame* self, ChessPlayer* player) {
	ChessPlayer* _tmp0_;
	ChessPlayer* _tmp1_;
	ChessPlayer* _tmp2_;
	GList* _tmp5_;
	GList* _tmp6_;
	GList* _tmp7_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (player != NULL);
	_tmp0_ = player;
	_tmp1_ = chess_game_get_current_player (self);
	_tmp2_ = _tmp1_;
	if (_tmp0_ == _tmp2_) {
		ChessPlayer* _tmp3_;
		ChessPlayer* _tmp4_;
		_tmp3_ = chess_game_get_opponent (self);
		_tmp4_ = _tmp3_;
		chess_game_undo_cb (self, _tmp4_);
	}
	_tmp5_ = self->move_stack;
	_tmp6_ = _tmp5_->next;
	if (_tmp6_ == NULL) {
		return;
	}
	_tmp7_ = self->move_stack;
	self->move_stack = g_list_remove_link (self->move_stack, _tmp7_);
	g_signal_emit_by_name (self, "undo");
}
