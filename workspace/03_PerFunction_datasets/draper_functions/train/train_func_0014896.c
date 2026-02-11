chess_scene_set_game (ChessScene* self, ChessGame* value) {
	ChessGame* _tmp0_;
	ChessGame* _tmp1_;
	ChessGame* _tmp2_;
	ChessGame* _tmp3_;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = _chess_game_ref0 (_tmp0_);
	_chess_game_unref0 (self->priv->_game);
	self->priv->_game = _tmp1_;
	self->priv->_move_number = -1;
	self->selected_rank = -1;
	self->selected_file = -1;
	_tmp2_ = self->priv->_game;
	g_signal_connect_object (_tmp2_, "moved", (GCallback) _chess_scene_moved_cb_chess_game_moved, self, 0);
	_tmp3_ = self->priv->_game;
	g_signal_connect_object (_tmp3_, "undo", (GCallback) _chess_scene_undo_cb_chess_game_undo, self, 0);
	chess_scene_update_board (self);
	g_object_notify ((GObject *) self, "game");
}
