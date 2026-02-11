set_transient_for(ManagedWindowHintInfo& info) {
    if (transient_for_ != nil) {
	XDrawable td = transient_for_->rep()->xwindow_;
	if (td != WindowRep::unbound) {
	    XSetTransientForHint(info.dpy_, info.xwindow_, td);
	    return true;
	}
    }
    return false;
}
