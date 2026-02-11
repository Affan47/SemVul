left() const {
    WindowRep& w = *rep();
    Display* d = w.display_;
    if (d == nil) {
	return w.left_;
    }
    w.check_position(this);
    return d->to_coord(w.xpos_);
}
