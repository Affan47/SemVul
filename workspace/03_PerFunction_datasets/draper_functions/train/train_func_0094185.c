gth_image_copy (GthImage *image)
{
	GthImage *new_image;

	new_image = gth_image_new ();

	switch (image->priv->format) {
	case GTH_IMAGE_FORMAT_CAIRO_SURFACE:
		new_image->priv->format = GTH_IMAGE_FORMAT_CAIRO_SURFACE;
		new_image->priv->data.surface = _cairo_image_surface_copy (image->priv->data.surface);
		break;

	case GTH_IMAGE_FORMAT_GDK_PIXBUF:
		new_image->priv->format = GTH_IMAGE_FORMAT_GDK_PIXBUF;
		new_image->priv->data.pixbuf = gdk_pixbuf_copy (image->priv->data.pixbuf);
		break;

	case GTH_IMAGE_FORMAT_GDK_PIXBUF_ANIMATION:
		new_image->priv->format = GTH_IMAGE_FORMAT_GDK_PIXBUF;
		new_image->priv->data.pixbuf = gdk_pixbuf_copy (gdk_pixbuf_animation_get_static_image (image->priv->data.pixbuf_animation));
		break;

	default:
		break;
	}

	return new_image;
}
