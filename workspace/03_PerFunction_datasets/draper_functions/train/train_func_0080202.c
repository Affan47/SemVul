chess_move_get_engine (ChessMove* self) {
	gchar* result = NULL;
	GString* _tmp0_;
	GString* builder;
	static const gchar promotion_symbols[] = {' ', 'r', 'n', 'b', 'q', ' '};
	ChessPiece* _tmp1_;
	GString* _tmp15_;
	const gchar* _tmp16_;
	gchar* _tmp17_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = g_string_new ("");
	builder = _tmp0_;
	_tmp1_ = self->promotion_piece;
	if (_tmp1_ != NULL) {
		GString* _tmp2_;
		gint _tmp3_;
		gint _tmp4_;
		gint _tmp5_;
		gint _tmp6_;
		ChessPiece* _tmp7_;
		PieceType _tmp8_;
		gchar _tmp9_;
		_tmp2_ = builder;
		_tmp3_ = self->f0;
		_tmp4_ = self->r0;
		_tmp5_ = self->f1;
		_tmp6_ = self->r1;
		_tmp7_ = self->promotion_piece;
		_tmp8_ = _tmp7_->type;
		_tmp9_ = promotion_symbols[_tmp8_];
		g_string_append_printf (_tmp2_, "%c%d%c%d%c", 'a' + _tmp3_, _tmp4_ + 1, 'a' + _tmp5_, _tmp6_ + 1, (gint) _tmp9_);
	} else {
		GString* _tmp10_;
		gint _tmp11_;
		gint _tmp12_;
		gint _tmp13_;
		gint _tmp14_;
		_tmp10_ = builder;
		_tmp11_ = self->f0;
		_tmp12_ = self->r0;
		_tmp13_ = self->f1;
		_tmp14_ = self->r1;
		g_string_append_printf (_tmp10_, "%c%d%c%d", 'a' + _tmp11_, _tmp12_ + 1, 'a' + _tmp13_, _tmp14_ + 1);
	}
	_tmp15_ = builder;
	_tmp16_ = _tmp15_->str;
	_tmp17_ = g_strdup (_tmp16_);
	result = _tmp17_;
	_g_string_free0 (builder);
	return result;
}
