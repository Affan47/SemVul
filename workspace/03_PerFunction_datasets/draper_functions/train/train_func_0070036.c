clip() {
    CanvasRep* c = rep();
    c->flush();
    PathRenderInfo* p = &CanvasRep::path_;
    int n = p->cur_point_ - p->point_;
    if (n <= 2) {
	return;
    }
    Region clip;
    XPoint* pt = p->point_;
    if (xrect(pt, n)) {
	XRectangle xr;
	xr.x = Math::min(pt[0].x, pt[2].x);
	xr.y = Math::min(pt[0].y, pt[2].y);
	xr.width = Math::abs(pt[0].x - pt[2].x);
	xr.height = Math::abs(pt[0].y - pt[2].y);
	clip = XCreateRegion();
	XUnionRectWithRegion(&xr, c->empty_, clip);
    } else {
	clip = XPolygonRegion(pt, n, EvenOddRule);
    }

    if (!XEmptyRegion(c->clipping_)) {
	Region intersect = XCreateRegion();
	XIntersectRegion(c->clipping_, clip, intersect);
	XDestroyRegion(clip);
	clip = intersect;
    }
    XDestroyRegion(c->clipping_);
    c->clipping_ = clip;
    XSetRegion(c->dpy(), c->drawgc_, clip);
}
