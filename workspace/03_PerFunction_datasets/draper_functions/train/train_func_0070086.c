gx_paint_box_call_paint_func(GxPaintBox *paint_box, GdkEventExpose *event)
{
	g_return_if_fail(GX_IS_PAINT_BOX(paint_box));
	if (paint_box->expose_func) {
		paint_box->expose_func(GTK_WIDGET(paint_box), event);
	}
}
