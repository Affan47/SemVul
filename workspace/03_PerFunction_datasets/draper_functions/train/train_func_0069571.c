_jpeg_exif_orientation_from_stream (GInputStream  *stream,
				    GCancellable  *cancellable,
				    GError       **error)
{
	GthTransform   orientation;

	orientation = GTH_TRANSFORM_NONE;

	if (_jpeg_read_segment_marker (stream, cancellable, error) == 0xd8) {
		if (_jpeg_skip_to_segment (stream, 0xe1, cancellable, error)) {
			guint   h, l;
			guint   app1_segment_size;
			guchar *app1_segment;

			h = _g_input_stream_read_byte (stream, cancellable, error);
			l = _g_input_stream_read_byte (stream, cancellable, error);
			app1_segment_size = (h << 8) + l - 2;

			app1_segment = g_new (guchar, app1_segment_size);
			if (g_input_stream_read (stream,
						 app1_segment,
						 app1_segment_size,
						 cancellable,
						 error) > 0)
			{
				orientation = _jpeg_exif_orientation_from_app1_segment (app1_segment, app1_segment_size);
			}

			g_free (app1_segment);
		}
	}

	return orientation;
}
