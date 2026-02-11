set_window (zword win)
{

    flush_buffer ();

    cwin = win; cwp = wp + win;

    update_attributes ();

    if (h_version == V6) {

	os_set_colour (lo (cwp->colour), hi (cwp->colour));

	if (os_font_data (cwp->font, &font_height, &font_width))
	    os_set_font (cwp->font);

	os_set_text_style (cwp->style);

    } else refresh_text_style ();

    if (h_version != V6 && win != 0) {
	wp[win].y_cursor = 1;
	wp[win].x_cursor = 1;
    }

    update_cursor ();

}
