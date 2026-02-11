active_context() {
	if(parent == NULL) return active;

	return active && parent->active_context();
}
