get_buffer_in_window(BW *bw, B *b)
{
	void *object = bw->object;
	W *w = bw->parent;
	if (b == bw->b) {
		return 0;

	}
	if (!b->orphan) {
		++b->count;
	} else {
		b->orphan = 0;
	}
	if (bw->b->count == 1) {
		orphit(bw);
	}
	bwrm(bw);
	w->object = (void *) (bw = bwmk(w, b, 0));
	wredraw(bw->parent);
	bw->object = object;
	return 0;
}
