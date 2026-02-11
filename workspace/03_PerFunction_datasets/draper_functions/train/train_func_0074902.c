minefield_view_real_get_preferred_width (GtkWidget* base, gint* minimum, gint* natural) {
	MinefieldView * self;
	gint _vala_minimum = 0;
	gint _vala_natural = 0;
	Minefield* _tmp0_ = NULL;
	Minefield* _tmp1_ = NULL;
	guint _tmp2_ = 0U;
	guint _tmp3_ = 0U;
	guint _tmp4_ = 0U;
	self = (MinefieldView*) base;
	_tmp0_ = minefield_view_get_minefield (self);
	_tmp1_ = _tmp0_;
	_tmp2_ = _tmp1_->width;
	_tmp3_ = minefield_view_get_minimum_size (self);
	_tmp4_ = _tmp3_;
	_vala_natural = (gint) (_tmp2_ * _tmp4_);
	_vala_minimum = _vala_natural;
	if (minimum) {
		*minimum = _vala_minimum;
	}
	if (natural) {
		*natural = _vala_natural;
	}
}
