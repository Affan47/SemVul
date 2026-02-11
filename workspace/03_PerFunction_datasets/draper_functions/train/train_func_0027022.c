fillRectangle( GdkPixbuf *pixbuf, DVColor bg )
{
	int ww = gdk_pixbuf_get_width( pixbuf );
	int hh = gdk_pixbuf_get_height( pixbuf );
	uint8_t *p = gdk_pixbuf_get_pixels( pixbuf );

	for ( int j = 0; j < hh; j++ )
	{
		for ( int i = 0; i < ww; i++ )
		{
			*p++ = bg.r;
			*p++ = bg.g;
			*p++ = bg.b;
			*p++ = bg.a;
		}
	}
}
