_gth_image_free_data (GthImage *self)
{
	switch (self->priv->format) {
	case GTH_IMAGE_FORMAT_CAIRO_SURFACE:
		cairo_surface_destroy (self->priv->data.surface);
		self->priv->data.surface = NULL;
		break;

	case GTH_IMAGE_FORMAT_GDK_PIXBUF:
		_g_object_unref (self->priv->data.pixbuf);
		self->priv->data.pixbuf = NULL;
		break;

	case GTH_IMAGE_FORMAT_GDK_PIXBUF_ANIMATION:
		_g_object_unref (self->priv->data.pixbuf_animation);
		self->priv->data.pixbuf_animation = NULL;
		break;

	default:
		break;
	}
}
