under_water(int mode)
{
    static xchar lastx, lasty;
    static bool dela;
    int x, y;


    if (Is_waterlevel(&u.uz) || u.uswallow) return;


    if (mode == 1 || dela) {
	cls();
	dela = false;
    }

    else if (mode == 2) {
	dela = true;
	return;
    }

    else {
	for (y = lasty-1; y <= lasty+1; y++)
	    for (x = lastx-1; x <= lastx+1; x++)
		if (isok(x,y))
		    show_glyph(x,y,cmap_to_glyph(S_stone));
    }
    for (x = u.ux-1; x <= u.ux+1; x++)
	for (y = u.uy-1; y <= u.uy+1; y++)
	    if (isok(x,y) && is_pool(x,y)) {
		if (Blind && !(x == u.ux && y == u.uy))
		    show_glyph(x,y,cmap_to_glyph(S_stone));
		else
		    newsym(x,y);
	    }
    lastx = u.ux;
    lasty = u.uy;
}
