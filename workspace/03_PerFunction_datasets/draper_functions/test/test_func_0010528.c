boxes_spice_display_real_get_pixbuf (BoxesDisplay* base, gint n, GError** error) {
	BoxesSpiceDisplay * self;
	GdkPixbuf* result = NULL;
	SpiceDisplay* display = NULL;
	gint _tmp0_ = 0;
	GtkWidget* _tmp1_ = NULL;
	SpiceDisplay* _tmp2_ = NULL;
	SpiceDisplay* _tmp3_ = NULL;
	gboolean _tmp4_ = FALSE;
	gboolean _tmp5_ = FALSE;
	SpiceDisplay* _tmp6_ = NULL;
	GdkPixbuf* _tmp7_ = NULL;
#line 164 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	self = (BoxesSpiceDisplay*) base;
#line 165 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	_tmp0_ = n;
#line 165 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	_tmp1_ = boxes_display_get_display ((BoxesDisplay*) self, _tmp0_);
#line 165 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	_tmp2_ = G_TYPE_CHECK_INSTANCE_TYPE (_tmp1_, spice_display_get_type ()) ? ((SpiceDisplay*) _tmp1_) : NULL;
#line 165 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	if (_tmp2_ == NULL) {
#line 165 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
		_g_object_unref0 (_tmp1_);
#line 1093 "spice-display.c"
	}
#line 165 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	display = _tmp2_;
#line 167 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	_tmp3_ = display;
#line 167 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	g_object_get (_tmp3_, "ready", &_tmp4_, NULL);
#line 167 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	_tmp5_ = _tmp4_;
#line 167 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	if (!_tmp5_) {
#line 168 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
		result = NULL;
#line 168 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
		_g_object_unref0 (display);
#line 168 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
		return result;
#line 1111 "spice-display.c"
	}
#line 170 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	_tmp6_ = display;
#line 170 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	_tmp7_ = spice_display_get_pixbuf (_tmp6_);
#line 170 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	result = _tmp7_;
#line 170 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	_g_object_unref0 (display);
#line 170 "/extra-data/checkout/gnome/gnome-boxes/src/spice-display.vala"
	return result;
#line 1123 "spice-display.c"
}
