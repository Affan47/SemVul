hist_new(int nx, int ny) {
	histogram2d* h = calloc(1, sizeof(histogram2d));
	if (!h) {
		ERROR("Couldn't allocate a histogram2d.");
		return NULL;
	}
	h->hist = calloc(nx*ny, sizeof(int));
	if (!h->hist) {
		ERROR("Couldn't allocate a histogram2d with %ix%i bins.", nx, ny);
		free(h);
		return NULL;
	}
	h->NX = nx;
	h->NY = ny;
	return h;
}
