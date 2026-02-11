gdk_pixbuf_new_from_resource_at_scale (const char *resource_path,
				       int         width,
				       int         height,
				       gboolean    preserve_aspect_ratio,
				       GError    **error)
{
	GInputStream *stream;
	GdkPixbuf *pixbuf;

	stream = g_resources_open_stream (resource_path, 0, error);
	if (stream == NULL)
		return NULL;

	pixbuf = gdk_pixbuf_new_from_stream_at_scale (stream, width, height, preserve_aspect_ratio, NULL, error);
	g_object_unref (stream);
	return pixbuf;
}
