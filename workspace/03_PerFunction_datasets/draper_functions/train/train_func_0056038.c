cursor(struct edwin *w, int x, int y)
{
    u8 buf0[40];
    u8 buf1[40];
    u8 buf2[32];

    if (w->edline)
	return;
    if (x < 0 || x >= W || y < 0 || y >= H)
	return;
    if (y == 0 && x < 8)
	return;

    xio_get_line(w->xw, 0, buf0);
    xio_get_line(w->xw, y, buf1);

    sprintf(buf2, "%2d\3%02x  \7    ", y, buf1[x]);
    buf2[6] = "CI"[w->mode];
    memcpy(buf0, buf2, 8);

    xio_put_line(w->xw, 0, buf0);
    xio_set_cursor(w->xw, w->x = x, w->y = y);
}
