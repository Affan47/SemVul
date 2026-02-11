key_value_renderer_real_render (GtkCellRenderer* base, cairo_t* context, GtkWidget* widget, GdkRectangle* background_area, GdkRectangle* cell_area, GtkCellRendererState flags) {
	KeyValueRenderer * self;
	GtkCellRenderer* _tmp0_;
	GtkCellRenderer* _tmp1_;
	cairo_t* _tmp2_;
	GtkWidget* _tmp3_;
	GdkRectangle _tmp4_;
	GdkRectangle _tmp5_;
	GtkCellRendererState _tmp6_;
	self = (KeyValueRenderer*) base;
	g_return_if_fail (context != NULL);
	g_return_if_fail (widget != NULL);
	g_return_if_fail (background_area != NULL);
	g_return_if_fail (cell_area != NULL);
	_tmp0_ = key_value_renderer_get_renderer (self);
	_tmp1_ = _tmp0_;
	_tmp2_ = context;
	_tmp3_ = widget;
	_tmp4_ = *background_area;
	_tmp5_ = *cell_area;
	_tmp6_ = flags;
	gtk_cell_renderer_render (_tmp1_, _tmp2_, _tmp3_, &_tmp4_, &_tmp5_, _tmp6_);
}
