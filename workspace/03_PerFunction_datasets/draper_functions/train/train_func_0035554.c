nraw0verts(
gamut *s
) {
	int i, nrv = 0;


	sort_verticies(s);


	for (i = 0; i < s->nv; i++) {
		if ((s->verts[i]->f & GVERT_SET)
		 && (s->verts[i]->k0 > 0))
			nrv++;
	}

	return nrv;
}
