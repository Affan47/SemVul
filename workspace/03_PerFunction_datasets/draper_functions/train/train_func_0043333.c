set_screen(int s) {
    DisplayRep& d = *rep();
    XDisplay* dpy = d.display_;
    if (s < 0 || s >= ScreenCount(dpy)) {
	return;
    }
    d.screen_ = s;
    d.root_ = RootWindow(dpy, s);
    d.default_visual_ = WindowVisual::find_visual(this, d.style_);
    d.pwidth_ = DisplayWidth(dpy, s);
    d.pheight_ = DisplayHeight(dpy, s);
    d.set_dpi(pixel_);
    point_ = 1.0 / pixel_;
    d.width_ = to_coord(d.pwidth_);
    d.height_ = to_coord(d.pheight_);
}
