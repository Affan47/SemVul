window_exist(int id) {
	window_t *w;

	for (w = windows; w; w = w->next) {
		if (w->id == id)
			return w;
	}

	return NULL;
}
