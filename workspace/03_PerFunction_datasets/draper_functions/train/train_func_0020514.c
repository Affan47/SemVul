handle_real_draw (GtkWidget* base, cairo_t* cr) {
	Handle * self;
	gboolean result = FALSE;
	cairo_t* _tmp0_ = NULL;
	GdkWindow* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	self = (Handle*) base;
	g_return_val_if_fail (cr != NULL, FALSE);
	_tmp0_ = cr;
	_tmp1_ = gtk_widget_get_window ((GtkWidget*) self);
	_tmp2_ = gtk_cairo_should_draw_window (_tmp0_, _tmp1_);
	if (_tmp2_) {
		GtkStyleContext* context = NULL;
		GtkStyleContext* _tmp3_ = NULL;
		GtkStyleContext* _tmp4_ = NULL;
		GtkAllocation allocation = {0};
		GtkAllocation _tmp5_ = {0};
		GtkStyleContext* _tmp6_ = NULL;
		cairo_t* _tmp7_ = NULL;
		GtkAllocation _tmp8_ = {0};
		gint _tmp9_ = 0;
		GtkAllocation _tmp10_ = {0};
		gint _tmp11_ = 0;
		GtkAllocation _tmp12_ = {0};
		gint _tmp13_ = 0;
		GtkAllocation _tmp14_ = {0};
		gint _tmp15_ = 0;
		_tmp3_ = gtk_widget_get_style_context ((GtkWidget*) self);
		_tmp4_ = _g_object_ref0 (_tmp3_);
		context = _tmp4_;
		gtk_widget_get_allocation ((GtkWidget*) self, &_tmp5_);
		allocation = _tmp5_;
		_tmp6_ = context;
		_tmp7_ = cr;
		_tmp8_ = allocation;
		_tmp9_ = _tmp8_.x;
		_tmp10_ = allocation;
		_tmp11_ = _tmp10_.y;
		_tmp12_ = allocation;
		_tmp13_ = _tmp12_.height;
		_tmp14_ = allocation;
		_tmp15_ = _tmp14_.width;
		gtk_render_handle (_tmp6_, _tmp7_, (gdouble) _tmp9_, (gdouble) (_tmp11_ + ((_tmp13_ - 40) / 2)), (gdouble) _tmp15_, 40.0);
		_g_object_unref0 (context);
	}
	result = FALSE;
	return result;
}
