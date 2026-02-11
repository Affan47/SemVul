set_image_from_data (EImageChooser *chooser,
                     gchar *data,
                     gint length)
{
	GdkPixbufLoader *loader;
	GdkPixbuf *pixbuf;
	gfloat scale;
	gint new_height;
	gint new_width;

	loader = gdk_pixbuf_loader_new ();
	gdk_pixbuf_loader_write (loader, (guchar *) data, length, NULL);
	gdk_pixbuf_loader_close (loader, NULL);

	pixbuf = gdk_pixbuf_loader_get_pixbuf (loader);
	if (pixbuf)
		g_object_ref (pixbuf);

	g_object_unref (loader);

	if (pixbuf == NULL)
		return FALSE;

	new_height = gdk_pixbuf_get_height (pixbuf);
	new_width = gdk_pixbuf_get_width (pixbuf);

	if (chooser->priv->image_height == 0
	    && chooser->priv->image_width == 0) {
		scale = 1.0;
	} else if (chooser->priv->image_height < new_height
		 || chooser->priv->image_width < new_width) {

		if (new_height > new_width)
			scale = (gfloat) chooser->priv->image_height / new_height;
		else
			scale = (gfloat) chooser->priv->image_width / new_width;
	} else {

		if (new_height > new_width)
			scale = (gfloat) new_height / chooser->priv->image_height;
		else
			scale = (gfloat) new_width / chooser->priv->image_width;
	}

	if (scale == 1.0) {
		gtk_image_set_from_pixbuf (
			GTK_IMAGE (chooser->priv->image), pixbuf);
		chooser->priv->image_width = new_width;
		chooser->priv->image_height = new_height;
	} else {
		GdkPixbuf *scaled;
		GdkPixbuf *composite;

		new_width *= scale;
		new_height *= scale;
		new_width = MIN (new_width, chooser->priv->image_width);
		new_height = MIN (new_height, chooser->priv->image_height);

		scaled = gdk_pixbuf_scale_simple (
			pixbuf, new_width, new_height,
			GDK_INTERP_BILINEAR);

		composite = gdk_pixbuf_new (
			GDK_COLORSPACE_RGB, TRUE,
			gdk_pixbuf_get_bits_per_sample (pixbuf),
			chooser->priv->image_width,
			chooser->priv->image_height);

		gdk_pixbuf_fill (composite, 0x00000000);

		gdk_pixbuf_copy_area (
			scaled, 0, 0, new_width, new_height,
			composite,
			chooser->priv->image_width / 2 - new_width / 2,
			chooser->priv->image_height / 2 - new_height / 2);

		gtk_image_set_from_pixbuf (
			GTK_IMAGE (chooser->priv->image), composite);

		g_object_unref (scaled);
		g_object_unref (composite);
	}

	g_object_unref (pixbuf);

	g_free (chooser->priv->image_buf);
	chooser->priv->image_buf = data;
	chooser->priv->image_buf_size = length;

	g_signal_emit (chooser, signals[CHANGED], 0);

	return TRUE;
}
