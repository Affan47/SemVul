img_convert_surface_to_pixbuf( cairo_surface_t *surface )
{
	GdkPixbuf *pixbuf;
	gint       w, h, ss, sp, row, col;
	guchar    *data_s, *data_p;


	w = cairo_image_surface_get_width( surface );
	h = cairo_image_surface_get_height( surface );
	ss = cairo_image_surface_get_stride( surface );
	data_s = cairo_image_surface_get_data( surface );


	pixbuf = gdk_pixbuf_new( GDK_COLORSPACE_RGB, FALSE, 8, w, h );


	sp = gdk_pixbuf_get_rowstride( pixbuf );
	data_p = gdk_pixbuf_get_pixels( pixbuf );


	for( row = 0; row < h; row++ )
	{
		for( col = 0; col < w; col++ )
		{
			gint index_s, index_p;

			index_s = row * ss + col * 4;
			index_p = row * sp + col * 3;

			data_p[index_p + 0] = data_s[index_s + 2];
			data_p[index_p + 1] = data_s[index_s + 1];
			data_p[index_p + 2] = data_s[index_s + 0];
		}
	}

	return( pixbuf );
}
