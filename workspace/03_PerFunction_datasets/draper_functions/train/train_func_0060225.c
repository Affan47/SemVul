gth_image_set_pixbuf (GthImage  *image,
		      GdkPixbuf *value)
{
	_gth_image_free_data (image);
	if (value == NULL)
		return;

	image->priv->format = GTH_IMAGE_FORMAT_GDK_PIXBUF;
	image->priv->data.pixbuf = g_object_ref (value);
}
