scroll_to(DimensionName d, Coord lower) {
    Coord p = lower;
    Coord prevdx = dx_;
    Coord prevdy = dy_;
    constrain(d, p);
    if (p != cur_lower(d)) {
	if (d == Dimension_X) dx_ = p;
	else dy_ = p;
	redraw();
	for (int i=0; i<page_->count(); i++) {
	    Coord x, y;
	    page_->location(i, x, y);
	    page_->move(i, x+prevdx-dx_, y+prevdy-dy_);
	}
	notify(d);
	redraw();
    };
}
