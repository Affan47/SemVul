Line(
    Canvas* c, IntCoord x1, IntCoord y1, IntCoord x2, IntCoord y2
) {
    if (c == nil) {
	return;
    }
    CanvasRep* cr = c->rep();
    if (cr->xdrawable_ == CanvasRep::unbound) {
	return;
    }
    IntCoord mx1, my1, mx2, my2;
    Map(c, x1, y1, mx1, my1);
    Map(c, x2, y2, mx2, my2);
    XDrawLine(cr->dpy(), cr->xdrawable_, rep->dashgc, mx1, my1, mx2, my2);
}
