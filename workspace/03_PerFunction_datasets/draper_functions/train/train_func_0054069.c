chess_state_is_in_checkmate (ChessState* self, ChessPlayer* player) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (player != NULL, FALSE);
	{
		gint piece_index;
		piece_index = 0;
		{
			gboolean _tmp0_;
			_tmp0_ = TRUE;
			while (TRUE) {
				gboolean _tmp1_;
				gint _tmp3_;
				gint _tmp4_;
				ChessPiece* _tmp5_;
				ChessPiece* _tmp6_;
				ChessPiece* p;
				gboolean _tmp7_ = FALSE;
				ChessPiece* _tmp8_;
				gboolean _tmp12_;
				_tmp1_ = _tmp0_;
				if (!_tmp1_) {
					gint _tmp2_;
					_tmp2_ = piece_index;
					piece_index = _tmp2_ + 1;
				}
				_tmp0_ = FALSE;
				_tmp3_ = piece_index;
				if (!(_tmp3_ < 64)) {
					break;
				}
				_tmp4_ = piece_index;
				_tmp5_ = self->board[_tmp4_];
				_tmp6_ = _chess_piece_ref0 (_tmp5_);
				p = _tmp6_;
				_tmp8_ = p;
				if (_tmp8_ != NULL) {
					ChessPiece* _tmp9_;
					ChessPlayer* _tmp10_;
					ChessPlayer* _tmp11_;
					_tmp9_ = p;
					_tmp10_ = _tmp9_->player;
					_tmp11_ = player;
					_tmp7_ = _tmp10_ == _tmp11_;
				} else {
					_tmp7_ = FALSE;
				}
				_tmp12_ = _tmp7_;
				if (_tmp12_) {
					{
						gint end;
						end = 0;
						{
							gboolean _tmp13_;
							_tmp13_ = TRUE;
							while (TRUE) {
								gboolean _tmp14_;
								gint _tmp16_;
								ChessPlayer* _tmp17_;
								gint _tmp18_;
								gint _tmp19_ = 0;
								gint _tmp20_;
								gint _tmp21_ = 0;
								gint _tmp22_;
								gint _tmp23_ = 0;
								gint _tmp24_;
								gint _tmp25_ = 0;
								gboolean _tmp26_ = FALSE;
								_tmp14_ = _tmp13_;
								if (!_tmp14_) {
									gint _tmp15_;
									_tmp15_ = end;
									end = _tmp15_ + 1;
								}
								_tmp13_ = FALSE;
								_tmp16_ = end;
								if (!(_tmp16_ < 64)) {
									break;
								}
								_tmp17_ = player;
								_tmp18_ = piece_index;
								_tmp19_ = chess_state_get_rank (self, _tmp18_);
								_tmp20_ = piece_index;
								_tmp21_ = chess_state_get_file (self, _tmp20_);
								_tmp22_ = end;
								_tmp23_ = chess_state_get_rank (self, _tmp22_);
								_tmp24_ = end;
								_tmp25_ = chess_state_get_file (self, _tmp24_);
								_tmp26_ = chess_state_move_with_coords (self, _tmp17_, _tmp19_, _tmp21_, _tmp23_, _tmp25_, PIECE_TYPE_QUEEN, FALSE, TRUE);
								if (_tmp26_) {
									result = FALSE;
									_chess_piece_unref0 (p);
									return result;
								}
							}
						}
					}
				}
				_chess_piece_unref0 (p);
			}
		}
	}
	result = TRUE;
	return result;
}
