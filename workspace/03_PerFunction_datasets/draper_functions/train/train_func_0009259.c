game_view_get_image_offset (GameView* self, gint number) {
	gint result = 0;
	gint set = 0;
	gint _tmp0_ = 0;
	gboolean _tmp1_ = FALSE;
	gint _tmp2_ = 0;
	gboolean _tmp4_ = FALSE;
	gint _tmp5_ = 0;
	gint _tmp7_ = 0;
	gint _tmp9_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = number;
	set = _tmp0_ / 4;
	_tmp2_ = number;
	if (_tmp2_ < 0) {
		_tmp1_ = TRUE;
	} else {
		gint _tmp3_ = 0;
		_tmp3_ = set;
		_tmp1_ = _tmp3_ >= 36;
	}
	_tmp4_ = _tmp1_;
	if (_tmp4_) {
		result = 42;
		return result;
	}
	_tmp5_ = set;
	if (_tmp5_ == 33) {
		gint _tmp6_ = 0;
		_tmp6_ = number;
		result = 33 + (_tmp6_ % 4);
		return result;
	}
	_tmp7_ = set;
	if (_tmp7_ == 35) {
		gint _tmp8_ = 0;
		_tmp8_ = number;
		result = 38 + (_tmp8_ % 4);
		return result;
	}
	_tmp9_ = set;
	if (_tmp9_ == 34) {
		result = 37;
		return result;
	}
	result = set;
	return result;
}
