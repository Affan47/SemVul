z_set_font (void)
{
    zword win = (h_version == V6) ? cwin : 0;
    zword font = zargs[0];

    if (font != 0) {

	if (os_font_data (font, &font_height, &font_width)) {

	    store (wp[win].font);

	    wp[win].font = font;
	    wp[win].font_size = (font_height << 8) | font_width;

	    if (!ostream_memory && ostream_screen && enable_buffering) {

		print_char (ZC_NEW_FONT);
		print_char (font);

	    } else os_set_font (font);

	} else store (0);

    } else store (wp[win].font);

}
