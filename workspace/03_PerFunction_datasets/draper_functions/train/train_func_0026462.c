wallify_map()
{
	unsigned int x, y, xx, yy, lo_xx, lo_yy, hi_xx, hi_yy;

	for (y = 0; y <= max_y_map; y++) {
	    SpinCursor(3);
	    lo_yy = (y > 0) ? y - 1 : 0;
	    hi_yy = (y < max_y_map) ? y + 1 : max_y_map;
	    for (x = 0; x <= max_x_map; x++) {
		if (Map_point(x,y) != STONE) continue;
		lo_xx = (x > 0) ? x - 1 : 0;
		hi_xx = (x < max_x_map) ? x + 1 : max_x_map;
		for (yy = lo_yy; yy <= hi_yy; yy++)
		    for (xx = lo_xx; xx <= hi_xx; xx++)
			if (IS_ROOM(Map_point(xx,yy)) ||
				Map_point(xx,yy) == CROSSWALL) {
			    Map_point(x,y) = (yy != y) ? HWALL : VWALL;
			    yy = hi_yy;
			    break;
			}
	    }
	}
}
