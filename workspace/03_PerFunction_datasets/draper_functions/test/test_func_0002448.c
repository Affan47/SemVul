style(Style* s) {
    DisplayRep& d = *rep();
    Resource::ref(s);
    Resource::unref(d.style_);
    d.style_ = s;
    set_screen(d.screen_);
    if (s->value_is_on("synchronous")) {
	XSynchronize(d.display_, True);
    }
}
