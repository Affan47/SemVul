game_view_real_button_press_event (GtkWidget* base, GdkEventButton* event) {
	GameView * self;
	gboolean result = FALSE;
	GdkEventButton _tmp0_;
	guint _tmp1_;
	self = (GameView*) base;
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = *event;
	_tmp1_ = _tmp0_.button;
	if (_tmp1_ == ((guint) 1)) {
		GdkEventButton _tmp2_;
		gdouble _tmp3_;
		gint _tmp4_;
		gint _tmp5_;
		gint _tmp6_;
		gint _tmp7_;
		gint x;
		GdkEventButton _tmp8_;
		gdouble _tmp9_;
		gint _tmp10_;
		gint _tmp11_;
		gint _tmp12_;
		gint _tmp13_;
		gint y;
		gboolean _tmp14_ = FALSE;
		gboolean _tmp15_ = FALSE;
		gboolean _tmp16_ = FALSE;
		gint _tmp17_;
		gboolean _tmp19_;
		gboolean _tmp21_;
		gboolean _tmp23_;
		_tmp2_ = *event;
		_tmp3_ = _tmp2_.x;
		_tmp4_ = game_view_get_x_offset (self);
		_tmp5_ = _tmp4_;
		_tmp6_ = game_view_get_tile_size (self);
		_tmp7_ = _tmp6_;
		x = ((gint) (_tmp3_ - _tmp5_)) / (_tmp7_ + GAME_VIEW_GRID_WIDTH);
		_tmp8_ = *event;
		_tmp9_ = _tmp8_.y;
		_tmp10_ = game_view_get_y_offset (self);
		_tmp11_ = _tmp10_;
		_tmp12_ = game_view_get_tile_size (self);
		_tmp13_ = _tmp12_;
		y = ((gint) (_tmp9_ - _tmp11_)) / (_tmp13_ + GAME_VIEW_GRID_WIDTH);
		_tmp17_ = x;
		if (_tmp17_ >= 0) {
			gint _tmp18_;
			_tmp18_ = x;
			_tmp16_ = _tmp18_ < 8;
		} else {
			_tmp16_ = FALSE;
		}
		_tmp19_ = _tmp16_;
		if (_tmp19_) {
			gint _tmp20_;
			_tmp20_ = y;
			_tmp15_ = _tmp20_ >= 0;
		} else {
			_tmp15_ = FALSE;
		}
		_tmp21_ = _tmp15_;
		if (_tmp21_) {
			gint _tmp22_;
			_tmp22_ = y;
			_tmp14_ = _tmp22_ < 8;
		} else {
			_tmp14_ = FALSE;
		}
		_tmp23_ = _tmp14_;
		if (_tmp23_) {
			gint _tmp24_;
			gint _tmp25_;
			_tmp24_ = x;
			_tmp25_ = y;
			g_signal_emit_by_name (self, "move", _tmp24_, _tmp25_);
		}
	}
	result = TRUE;
	return result;
}
