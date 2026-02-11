startnexttri(gamut *s) {
	if IS_LIST_EMPTY(s->tris)
		triangulate(s);

	s->nexttri = NULL;
}
