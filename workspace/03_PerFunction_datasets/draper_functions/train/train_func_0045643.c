do_clear_area(scol,srow,range,func,arg)
    int scol, srow, range;
    void FDECL((*func), (int,int,genericptr_t));
    genericptr_t arg;
{

	if (scol != u.ux || srow != u.uy)
	    view_from(srow, scol, (char **)0, (char *)0, (char *)0,
							range, func, arg);
	else {
	    register int x;
	    int y, min_x, max_x, max_y, offset;
	    char *limits;

	    if (range > MAX_RADIUS || range < 1)
		panic("do_clear_area:  illegal range %d", range);
	    if(vision_full_recalc)
		vision_recalc(0);
	    limits = circle_ptr(range);
	    if ((max_y = (srow + range)) >= ROWNO) max_y = ROWNO-1;
	    if ((y = (srow - range)) < 0) y = 0;
	    for (; y <= max_y; y++) {
		offset = limits[v_abs(y-srow)];
		if((min_x = (scol - offset)) < 0) min_x = 0;
		if((max_x = (scol + offset)) >= COLNO) max_x = COLNO-1;
		for (x = min_x; x <= max_x; x++)
		    if (couldsee(x, y))
			(*func)(x, y, arg);
	    }
	}
}
