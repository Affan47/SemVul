chess_state_get_file (ChessState* self, gint index) {
	gint result = 0;
	gint _tmp0_;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = index;
	result = _tmp0_ % 8;
	return result;
}
