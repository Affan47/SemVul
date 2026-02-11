del_gverts(gamut *s) {
	int i;
	for (i = 0; i < s->nv; i++) {
		free(s->verts[i]);
	}
	if (s->verts != NULL) {
		free(s->verts);
		s->na = 0;
		s->nv = 0;
	}
}
