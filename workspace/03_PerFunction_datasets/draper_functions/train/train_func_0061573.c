window_find_ptr(window_t *w) {
	window_t *v;

	for (v = windows; v; v = v->next) {
		if (w == v)
			return w;
	}
	return NULL;
}
