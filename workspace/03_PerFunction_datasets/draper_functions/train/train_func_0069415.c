boxes_display_access_finish (BoxesDisplay* self) {
	gint64 _tmp0_ = 0LL;
	gint64 duration = 0LL;
	gint64 _tmp1_ = 0LL;
	gint64 _tmp2_ = 0LL;
	gint64 _tmp3_ = 0LL;
	BoxesBoxConfig* _tmp4_ = NULL;
	BoxesBoxConfig* _tmp5_ = NULL;
	gint64 _tmp6_ = 0LL;
	gint64 _tmp7_ = 0LL;
	gint64 _tmp8_ = 0LL;
#line 54 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	g_return_if_fail (self != NULL);
#line 55 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_tmp0_ = self->priv->started_time;
#line 55 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	if (_tmp0_ == ((gint64) 0)) {
#line 56 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
		return;
#line 419 "display.c"
	}
#line 58 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_tmp1_ = g_get_monotonic_time ();
#line 58 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_tmp2_ = self->priv->started_time;
#line 58 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	duration = _tmp1_ - _tmp2_;
#line 59 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_tmp3_ = duration;
#line 59 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	duration = _tmp3_ / 1000000;
#line 60 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_tmp4_ = self->priv->_config;
#line 60 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_tmp5_ = self->priv->_config;
#line 60 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_tmp6_ = boxes_box_config_get_access_total_time (_tmp5_);
#line 60 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_tmp7_ = _tmp6_;
#line 60 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_tmp8_ = duration;
#line 60 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	boxes_box_config_set_access_total_time (_tmp5_, _tmp7_ + _tmp8_);
#line 62 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	self->priv->started_time = (gint64) 0;
#line 445 "display.c"
}
