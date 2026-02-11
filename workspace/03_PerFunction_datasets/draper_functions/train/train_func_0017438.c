hypermaze_getmove_kb (Pos *pos, int key, byte **movp, int **rmovp)
{

	int curx = -1, cury = -1;
	int incx = -1, incy = -1;
	int x, y;
	hypermaze_get_cur_pos (pos->board, &curx, &cury);
	g_assert (curx >= 0 && cury >= 0);
	switch (key)
	{
		case GDK_KP_Home: incx = -2; incy = 2; break;
		case GDK_KP_Page_Up: incx = 2; incy = 2; break;
		case GDK_KP_End: incx = -2; incy = -2; break;
		case GDK_KP_Page_Down: incx = 2; incy = -2; break;
		case GDK_Up:
		case GDK_KP_Up: incx = 0; incy = 2; break;
		case GDK_Down:
		case GDK_KP_Down: incx = 0; incy = -2; break;
		case GDK_Right:
		case GDK_KP_Right: incx = 2; incy = 0; break;
		case GDK_Left:
		case GDK_KP_Left: incx = -2; incy = 0; break;
		default: return -1;
	}
	x = curx + incx;
	y = cury + incy;
	return hypermaze_getmove_common (pos, movp, x, y, curx, cury, incx, incy);
}
