rep(Display* d) const {
    BrushRep* r;
    BrushRepList& list = *impl_->replist;
    for (ListItr(BrushRepList) i(list); i.more(); i.next()) {
	r = i.cur();
	if (r->display_ == d) {
	    return r;
	}
    }
    r = new BrushRep;
    r->display_ = d;
    r->dash_list_ = impl_->dash_list;
    r->dash_count_ = impl_->dash_count;
    r->width_ = d->to_pixels(impl_->width);
    list.append(r);
    return r;
}
