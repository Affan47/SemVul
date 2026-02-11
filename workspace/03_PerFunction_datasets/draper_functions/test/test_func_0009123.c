SetVPos(ScrollableWidget gw, long pos_y)
{
    ScrListWidget	w = (ScrListWidget)gw;
    Display		*disp = XtDisplay(w);
    Window		win = XtWindow(w);
    long		old = FIRST(w);
    long		diff;
    long		n = SHOWN(w);
    int			y = w->scrlist.internal_height;
    int			dy = 0;

    if (LINES(w) <= 0)
	return;

    if (pos_y > LINES(w) - SHOWN(w))
	pos_y = LINES(w) - SHOWN(w);
    if (pos_y < 0)
	pos_y = 0;

    diff = pos_y - old;
    FIRST(w) = pos_y;
    if (w->scrlist.strings)
	dy = w->scrlist.font->ascent + w->scrlist.font->descent;
    if (w->scrlist.pixmaps && (int)w->scrlist.pixmap_height > dy)
	dy = w->scrlist.pixmap_height;
    dy += 2 * (w->scrlist.internal_item_height + w->shadow.shadow_width) +
	w->scrlist.row_spacing;
    if (dy == 0 || diff == 0 || !XtIsRealized((Widget)w))
	return;

    if (diff <= -n || diff >= n) {
	XClearWindow(disp, win);
	redraw_items(w, pos_y, pos_y + n - 1, False);
    } else if (diff < 0) {
	XCopyArea(disp, win, win, w->scrlist.default_gc,
		  0, y,
		  w->core.width, (n + diff) * dy,
		  0, y - diff * dy);
	XClearArea(disp, win, 0, 0, 0, y - diff * dy, False);
	redraw_items(w, pos_y, pos_y - diff - 1, False);
    } else if (diff > 0) {
	XCopyArea(disp, win, win, w->scrlist.default_gc,
		  0, y + diff * dy,
		  w->core.width, (n - diff) * dy,
		  0, y);
	XClearArea(disp, win, 0, y + (n - diff) * dy, 0, 0, False);
	redraw_items(w, pos_y + n - diff, pos_y + n - 1, False);
    }
}
