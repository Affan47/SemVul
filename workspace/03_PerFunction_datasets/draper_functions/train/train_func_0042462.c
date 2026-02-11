gth_image_viewer_page_copy_image (GthImageViewerPage *self)
{
	cairo_surface_t *image;
	GtkClipboard    *clipboard;
	GdkPixbuf       *pixbuf;

	image = gth_image_viewer_get_current_image (GTH_IMAGE_VIEWER (self->priv->viewer));
	if (image == NULL)
		return;

	clipboard = gtk_clipboard_get_for_display (gtk_widget_get_display (self->priv->viewer), GDK_SELECTION_CLIPBOARD);
	pixbuf = _gdk_pixbuf_new_from_cairo_surface (image);
	gtk_clipboard_set_image (clipboard, pixbuf);

	g_object_unref (pixbuf);
}
