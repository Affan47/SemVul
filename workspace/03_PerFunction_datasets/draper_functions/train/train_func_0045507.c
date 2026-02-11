split_window (zword height)
{
    zword stat_height = 0;

    flush_buffer ();


    if (h_version != V6)
	height *= hi (wp[1].font_size);

    if (h_version <= V3)
	stat_height = hi (wp[7].font_size);


    wp[1].y_cursor += wp[1].y_pos - 1 - stat_height;

    wp[1].y_pos = 1 + stat_height;
    wp[1].y_size = height;

    if ((short) wp[1].y_cursor > (short) wp[1].y_size)
	reset_cursor (1);


    wp[0].y_cursor += wp[0].y_pos - 1 - stat_height - height;

    wp[0].y_pos = 1 + stat_height + height;
    wp[0].y_size = h_screen_height - stat_height - height;

    if ((short) wp[0].y_cursor < 1)
	reset_cursor (0);


    if (h_version == V3 && height != 0)
	erase_window (1);

}
