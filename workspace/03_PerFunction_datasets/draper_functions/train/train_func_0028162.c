font(const Font* f) {
    CanvasRep& c = *this;
    if (f != nil && f != c.font_) {
	Resource::ref(f);
	Resource::unref(c.font_);
	FontRep* fr = f->rep(c.display_);
	c.font_ = f;
	XFontStruct* xf = fr->font_;
        c.xfont_ = xf;
        c.text_twobyte_ = xf->min_byte1 > 0 || xf->max_byte1 > 0;
	const char* coding = f->Font::encoding();
	c.text_reencode_ = coding != nil && strcmp(coding, "ISO8859") == 0;
	if (fr->unscaled_) {
	    c.font_is_scaled_ = false;
	} else {
	    c.font_is_scaled_ = true;
	    float tolerance = 0.15;
	    Window* w = c.window_;
	    if (w != nil) {
		Style* s = w->style();
		if (s != nil) {
		    s->find_attribute("fontScaleTolerance", tolerance);
		}
	    }
	    c.font_is_scaled_ = (
		fr->scale_ < (1 - tolerance) || fr->scale_ > (1 + tolerance)
	    );
	}
        XSetFont(c.dpy(), c.drawgc_, xf->fid);
    }
}
