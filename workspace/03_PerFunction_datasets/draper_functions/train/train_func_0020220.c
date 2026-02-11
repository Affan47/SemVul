set_attributes() {
    WindowRep& w = *rep();

    if (w.visual_ == nil) {
	w.visual_ = WindowVisual::find_visual(w.display_, w.style_);
    }

    w.xattrmask_ |= CWBackPixmap;
    w.xattrs_.background_pixmap = None;


    w.xattrmask_ |= CWBorderPixel;
    w.xattrs_.border_pixel = 0;

    if (w.style_->value_is_on("backingStore")) {
	w.xattrmask_ |= CWBackingStore;
	w.xattrs_.backing_store = WhenMapped;
    }

    if (w.style_->value_is_on("saveUnder")) {
	w.xattrmask_ |= CWSaveUnder;
	w.xattrs_.save_under = true;
    }

    w.xattrmask_ |= CWEventMask;
    w.xattrs_.event_mask = (
	KeyPressMask | KeyReleaseMask |
	ButtonPressMask | ButtonReleaseMask |
	PointerMotionMask | PointerMotionHintMask |
	EnterWindowMask | LeaveWindowMask |
	ExposureMask |
	StructureNotifyMask |
	FocusChangeMask |
	OwnerGrabButtonMask
    );


    w.xattrmask_ |= CWDontPropagate;
    w.xattrs_.do_not_propagate_mask = (
	KeyPressMask | KeyReleaseMask |
	ButtonPressMask | ButtonReleaseMask | PointerMotionMask
    );

    w.xattrmask_ |= CWColormap;
    w.xattrs_.colormap = w.visual_->colormap();

    if (w.cursor_ != nil) {
	w.xattrmask_ |= CWCursor;
	w.xattrs_.cursor = w.cursor_->rep()->xid(w.display_, w.visual_);
    }
}
