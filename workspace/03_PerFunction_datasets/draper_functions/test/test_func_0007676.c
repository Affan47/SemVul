display_line(int line, int color, int flsh)
{
    int type, symb;
    static struct line_pnts *Points;
    static struct line_cats *Cats;
    static int first = 1;

    G_debug(2, "display_line(): line = %d color = %d", line, color);

    if (first) {
	Points = Vect_new_line_struct();
	Cats = Vect_new_cats_struct();
	first = 0;
    }

    if (!Vect_line_alive(&Map, line))
	return;

    type = Vect_read_line(&Map, Points, Cats, line);

    if (color == SYMB_DEFAULT)
	symb = LineSymb[line];
    else
	symb = color;

    symb_set_driver_color(symb);

    if (type & GV_POINTS)
	display_icon(Points->x[0], Points->y[0], G_ICON_CROSS, 0, 6, flsh);
    else
	display_points(Points, flsh);

}
