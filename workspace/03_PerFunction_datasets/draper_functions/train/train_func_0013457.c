do_bind(Window* w, XWindow parent, int left, int top) {
    CanvasRep& c = *canvas_->rep();
    DisplayRep& d = *display_->rep();
    XDisplay* dpy = d.display_;
    WindowTable& t = *d.wtable_;
    if (xwindow_ != WindowRep::unbound) {
	t.remove(xwindow_);
    }
    w->set_attributes();
    xwindow_ = XCreateWindow(
	dpy, parent, left, top, canvas_->pwidth(), canvas_->pheight(),
	 0, visual_->depth(), xclass_,
	visual_->visual(), xattrmask_, &xattrs_
    );
    c.xdrawable_ = xwindow_;
    t.insert(xwindow_, w);
    xtoplevel_ = toplevel_->rep()->xwindow_;
}
