walk_path(src_cc, dest_cc, check_proc, arg)
    coord *src_cc;
    coord *dest_cc;
    boolean FDECL((*check_proc), (genericptr_t, int, int));
    genericptr_t arg;
{
    int x, y, dx, dy, x_change, y_change, err, i, prev_x, prev_y;
    boolean keep_going = TRUE;


    dx = dest_cc->x - src_cc->x;
    dy = dest_cc->y - src_cc->y;
    prev_x = x = src_cc->x;
    prev_y = y = src_cc->y;

    if (dx < 0) {
	x_change = -1;
	dx = -dx;
    } else
	x_change = 1;
    if (dy < 0) {
	y_change = -1;
	dy = -dy;
    } else
	y_change = 1;

    i = err = 0;
    if (dx < dy) {
	while (i++ < dy) {
	    prev_x = x;
	    prev_y = y;
	    y += y_change;
	    err += dx;
	    if (err >= dy) {
		x += x_change;
		err -= dy;
	    }

	if (!(keep_going = (*check_proc)(arg, x, y)))
	    break;
	}
    } else {
	while (i++ < dx) {
	    prev_x = x;
	    prev_y = y;
	    x += x_change;
	    err += dy;
	    if (err >= dx) {
		y += y_change;
		err -= dx;
	    }

	if (!(keep_going = (*check_proc)(arg, x, y)))
	    break;
	}
    }

    if (keep_going)
	return TRUE;

    dest_cc->x = prev_x;
    dest_cc->y = prev_y;
    return FALSE;
}
