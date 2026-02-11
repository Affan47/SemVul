fill(const Color* color) {
    CanvasRep* c = rep();
    PathRenderInfo* p = &CanvasRep::path_;
    int n = p->cur_point_ - p->point_;
    if (n <= 2) {
	return;
    }
    c->flush();
    c->color(color);
    XDisplay* dpy = c->display_->rep()->display_;
    XDrawable d = c->drawbuffer_;
    GC gc = c->drawgc_;
    XPoint* pt = p->point_;
    if (xrect(pt, n)) {
        int x = Math::min(pt[0].x, pt[2].x);
        int y = Math::min(pt[0].y, pt[2].y);
        int w = Math::abs(pt[0].x - pt[2].x);
        int h = Math::abs(pt[0].y - pt[2].y);
        XFillRectangle(dpy, d, gc, x, y, w, h);
    } else {
        XFillPolygon(dpy, d, gc, pt, n, Complex, CoordModeOrigin);
    }
}
