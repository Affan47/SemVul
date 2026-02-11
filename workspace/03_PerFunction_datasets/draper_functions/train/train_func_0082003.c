gth_image_get_cairo_surface (GthImage *image)
{
	cairo_surface_t *result = NULL;

	switch (image->priv->format) {
	case GTH_IMAGE_FORMAT_CAIRO_SURFACE:
		result = cairo_surface_reference (image->priv->data.surface);
		break;

	case GTH_IMAGE_FORMAT_GDK_PIXBUF:
		result = _cairo_image_surface_create_from_pixbuf (image->priv->data.pixbuf);
		break;

	case GTH_IMAGE_FORMAT_GDK_PIXBUF_ANIMATION:
		if (image->priv->data.pixbuf_animation != NULL) {
			GdkPixbuf *static_image;

			static_image = gdk_pixbuf_animation_get_static_image (image->priv->data.pixbuf_animation);
			result = _cairo_image_surface_create_from_pixbuf (static_image);
		}
		break;

	default:
		break;
	}

	return result;
}
