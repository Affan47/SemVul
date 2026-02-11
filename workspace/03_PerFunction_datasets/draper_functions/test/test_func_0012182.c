property_panel_set_cursor_location (PropertyPanel* self, gint x, gint y, gint width, gint height) {
	GdkRectangle location = {0};
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	GdkRectangle _tmp4_ = {0};
	GdkRectangle _tmp5_ = {0};
	GdkRectangle _tmp6_ = {0};
	gint _tmp7_ = 0;
	gint _tmp8_ = 0;
	gint _tmp9_ = 0;
	gint _tmp10_ = 0;
	gint _tmp11_ = 0;
	GdkRectangle _tmp19_ = {0};
	g_return_if_fail (self != NULL);
	_tmp0_ = x;
	_tmp1_ = y;
	_tmp2_ = width;
	_tmp3_ = height;
	memset (&_tmp4_, 0, sizeof (GdkRectangle));
	_tmp4_.x = _tmp0_;
	_tmp4_.y = _tmp1_;
	_tmp4_.width = _tmp2_;
	_tmp4_.height = _tmp3_;
	location = _tmp4_;
	_tmp5_ = self->priv->m_cursor_location;
	_tmp6_ = location;
	if (_cairo_rectangle_int_equal (&_tmp5_, &_tmp6_) == TRUE) {
		return;
	}
	_tmp7_ = x;
	_tmp8_ = y;
	_tmp9_ = width;
	_tmp10_ = height;
	g_debug ("propertypanel.vala:108: set_cursor_location(x = %d, y = %d, width = %d" \
", height = %d)\n", _tmp7_, _tmp8_, _tmp9_, _tmp10_);
	_tmp11_ = self->priv->m_show;
	if (_tmp11_ == ((gint) PANEL_SHOW_AUTO_HIDE)) {
		gboolean _tmp12_ = FALSE;
		GdkRectangle _tmp13_ = {0};
		gint _tmp14_ = 0;
		gboolean _tmp17_ = FALSE;
		_tmp13_ = self->priv->m_cursor_location;
		_tmp14_ = _tmp13_.x;
		if (_tmp14_ != (-1)) {
			_tmp12_ = TRUE;
		} else {
			GdkRectangle _tmp15_ = {0};
			gint _tmp16_ = 0;
			_tmp15_ = self->priv->m_cursor_location;
			_tmp16_ = _tmp15_.y;
			_tmp12_ = _tmp16_ != (-1);
		}
		_tmp17_ = _tmp12_;
		if (_tmp17_) {
			GdkRectangle _tmp18_ = {0};
			_tmp18_ = location;
			self->priv->m_cursor_location = _tmp18_;
			property_panel_hide_if_necessary (self);
			property_panel_adjust_window_position (self);
			return;
		}
	}
	_tmp19_ = location;
	self->priv->m_cursor_location = _tmp19_;
	property_panel_adjust_window_position (self);
	property_panel_show_with_auto_hide_timer (self);
}
