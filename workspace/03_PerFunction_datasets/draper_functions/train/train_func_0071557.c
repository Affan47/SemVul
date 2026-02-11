nverts(
gamut *s
) {
	if IS_LIST_EMPTY(s->tris)
		triangulate(s);

	return s->ntv;
}
