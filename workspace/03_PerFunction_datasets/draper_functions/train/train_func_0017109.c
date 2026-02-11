gtk_zoomed_update(GtkZoomed* zoomed, math::Vec2<int>& pointer, math::Vec2<int>& screen_size, math::Vec2<int>& offset, GdkPixbuf* pixbuf){
	GtkZoomedPrivate *ns=GTK_ZOOMED_GET_PRIVATE(zoomed);

  ns->pointer = pointer;
	ns->screen_size = screen_size;

	gint32 x=pointer.x, y=pointer.y;
	gint32 width=screen_size.x, height=screen_size.y;

	gint32 left, right, top, bottom;

	gint32 area_width = uint32_t(ns->width_height * zoom_transformation(ns->zoom));
	if (!area_width) area_width = 1;

	left	= x - area_width / 2;
	top		= y - area_width / 2;
	right	= x + (area_width - area_width / 2);
	bottom	= y + (area_width - area_width / 2);

	if (left < 0){
		right += -left;
		left=0;
	}
	if (right > width){
		left -= right - width;
		right = width;
	}
	if (top < 0){
		bottom += -top;
		top = 0;
	}
	if (bottom > height){
		top -= bottom - height;
		bottom = height;
	}

	gint32 xl = ((x - left) * ns->width_height) / area_width;
	gint32 xh = (((x + 1) - left) * ns->width_height) / area_width;
	gint32 yl = ((y - top) * ns->width_height) / area_width;
	gint32 yh = (((y + 1) - top) * ns->width_height) / area_width;

	ns->point.x = (xl + xh) / 2.0;
	ns->point.y = (yl + yh) / 2.0;
	ns->point_size.x = xh - xl;
	ns->point_size.y = yh - yl;

	width	= right - left;
	height	= bottom - top;

	gdk_pixbuf_scale(pixbuf, ns->pixbuf, 0, 0, ns->width_height, ns->width_height, -offset.x * ns->width_height / (double)width, -offset.y * ns->width_height / (double)height, ns->width_height / (double)width, ns->width_height / (double)height, GDK_INTERP_NEAREST);

	gtk_widget_queue_draw(GTK_WIDGET(zoomed));

}
