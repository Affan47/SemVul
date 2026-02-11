make_transparent_image(GdkDrawable *drawable, char **xpm,
    const char *tooltip)
{
	GdkPixmap *pixmap;
	GdkBitmap *mask;
	GtkWidget *image;

	pixmap = gdk_pixmap_create_from_xpm_d(drawable, &mask, NULL, xpm);
	image = gtk_image_new_from_pixmap(pixmap, mask);
	gtk_misc_set_padding(GTK_MISC(image), 1, 1);
	if (tooltip)
		gtk_widget_set_tooltip_markup(image, tooltip);
	return image;
}
