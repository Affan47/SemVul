puzzle_view_move_tile (PuzzleView* self, TileImage* image, gdouble x, gdouble y, gdouble duration) {
	gboolean _tmp0_ = FALSE;
	TileImage* _tmp1_;
	gdouble _tmp2_;
	gdouble _tmp3_;
	gboolean _tmp7_;
	TileImage* _tmp8_;
	TileImage* _tmp9_;
	gdouble _tmp10_;
	TileImage* _tmp11_;
	TileImage* _tmp12_;
	gdouble _tmp13_;
	TileImage* _tmp14_;
	GTimer* _tmp15_;
	gdouble _tmp16_ = 0.0;
	TileImage* _tmp17_;
	gdouble _tmp18_;
	TileImage* _tmp19_;
	gdouble _tmp20_;
	TileImage* _tmp21_;
	gdouble _tmp22_;
	gdouble _tmp23_;
	guint _tmp32_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (image != NULL);
	_tmp1_ = image;
	_tmp2_ = _tmp1_->x;
	_tmp3_ = x;
	if (_tmp2_ == _tmp3_) {
		TileImage* _tmp4_;
		gdouble _tmp5_;
		gdouble _tmp6_;
		_tmp4_ = image;
		_tmp5_ = _tmp4_->y;
		_tmp6_ = y;
		_tmp0_ = _tmp5_ == _tmp6_;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp7_ = _tmp0_;
	if (_tmp7_) {
		return;
	}
	_tmp8_ = image;
	_tmp9_ = image;
	_tmp10_ = _tmp9_->x;
	_tmp8_->source_x = _tmp10_;
	_tmp11_ = image;
	_tmp12_ = image;
	_tmp13_ = _tmp12_->y;
	_tmp11_->source_y = _tmp13_;
	_tmp14_ = image;
	_tmp15_ = self->priv->animation_timer;
	_tmp16_ = g_timer_elapsed (_tmp15_, NULL);
	_tmp14_->source_time = _tmp16_;
	_tmp17_ = image;
	_tmp18_ = x;
	_tmp17_->target_x = _tmp18_;
	_tmp19_ = image;
	_tmp20_ = y;
	_tmp19_->target_y = _tmp20_;
	_tmp21_ = image;
	_tmp22_ = duration;
	_tmp21_->duration = _tmp22_;
	_tmp23_ = duration;
	if (_tmp23_ == ((gdouble) 0)) {
		TileImage* _tmp24_;
		TileImage* _tmp25_;
		TileImage* _tmp26_;
		gdouble _tmp27_;
		TileImage* _tmp28_;
		TileImage* _tmp29_;
		gdouble _tmp30_;
		TileImage* _tmp31_;
		_tmp24_ = image;
		puzzle_view_redraw_tile (self, _tmp24_);
		_tmp25_ = image;
		_tmp26_ = image;
		_tmp27_ = _tmp26_->target_x;
		_tmp25_->x = _tmp27_;
		_tmp28_ = image;
		_tmp29_ = image;
		_tmp30_ = _tmp29_->target_y;
		_tmp28_->y = _tmp30_;
		_tmp31_ = image;
		puzzle_view_redraw_tile (self, _tmp31_);
		return;
	}
	_tmp32_ = self->priv->animation_timeout;
	if (_tmp32_ == ((guint) 0)) {
		guint _tmp33_ = 0U;
		_tmp33_ = g_timeout_add_full (G_PRIORITY_DEFAULT, (guint) 10, _puzzle_view_animate_cb_gsource_func, g_object_ref (self), g_object_unref);
		self->priv->animation_timeout = _tmp33_;
	}
}
