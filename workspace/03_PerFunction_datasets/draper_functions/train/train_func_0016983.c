getPixbuf( DVColor fg, DVColor bg, int outline, DVColor outlinecolor, bool isMarkup )
{
	pango_layout_set_width( layout,  -1 );
	pango_layout_set_font_description( layout, font );
	pango_layout_set_spacing( layout, space );
	pango_layout_set_alignment( layout, static_cast< PangoAlignment >( align ) );
	if ( isMarkup )
	{
		pango_layout_set_text( layout, "", -1 );
		pango_layout_set_markup( layout, text, (text == NULL ? 0 : strlen( text ) ) );
	}
	else
	{
		pango_layout_set_markup( layout, "", -1 );
		pango_layout_set_text( layout, text, (text == NULL ? 0 : strlen( text ) ) );
	}
	pango_layout_get_pixel_size( layout, &w, &h );

	GdkPixbuf *pixbuf = gdk_pixbuf_new( GDK_COLORSPACE_RGB,
	                                    TRUE,
	                                    8,
	                                    w + 2 * padw, h + 2 * padh );
	if ( pixbuf )
	{
		fillRectangle( pixbuf, bg );
		drawPixbuf( pixbuf, fg, bg, outline, outlinecolor );
	}

	return pixbuf;
}
