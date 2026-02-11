check_binding(Window* w) {
    if (unmapped_) {
	w->unbind();
    }
}
