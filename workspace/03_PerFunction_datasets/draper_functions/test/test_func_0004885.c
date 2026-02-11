do_set(Window* window, HintFunction f) {
    WindowRep& w = *window->rep();
    ManagedWindowHintInfo info;
    info.xwindow_ = w.xwindow_;
    if (info.xwindow_ != WindowRep::unbound) {
	info.style_ = w.style_;
	info.dpy_ = w.dpy();
	info.hints_ = XGetWMHints(info.dpy_, info.xwindow_);
	if (info.hints_ == nil) {
	    info.hints_ = XAllocWMHints();
	}
	info.pwidth_ = w.canvas_->pwidth();
	info.pheight_ = w.canvas_->pheight();
	info.display_ = w.display_;
	if ((this->*f)(info)) {
	    XSetWMHints(info.dpy_, info.xwindow_, info.hints_);
	}
	XFree((char*)info.hints_);
    }
}
