z_get_cursor (void)
{
    zword y, x;

    flush_buffer ();

    y = cwp->y_cursor;
    x = cwp->x_cursor;

    if (h_version != V6) {
	y = (y - 1) / h_font_height + 1;
	x = (x - 1) / h_font_width + 1;
    }

    storew ((zword) (zargs[0] + 0), y);
    storew ((zword) (zargs[0] + 2), x);

}
