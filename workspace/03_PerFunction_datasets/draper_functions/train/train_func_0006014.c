drag(const Event& e) {
    if (dragging_) {
	if (!(at_start() && at_end())) {
	    drag_to(e);
	}
    }
}
