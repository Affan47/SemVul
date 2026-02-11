get_image_dimensions(GtkWidget *widget, GdkPixbuf *pb,
				 GdkRectangle *rect, gint *frame_count)
{
	gtk_widget_style_get(widget, "framecount", frame_count, NULL);

	rect->width  = gdk_pixbuf_get_width(pb);
	rect->height = gdk_pixbuf_get_height(pb);

	if (*frame_count >1) {
		rect->width = (rect->width / *frame_count);
	}
	if (*frame_count == 0) {
		*frame_count = rect->width / rect->height;
		rect->width = rect->height;
	}
}
