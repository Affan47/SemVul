vtx_cache_get(ofps *s, int *nix) {
	int e, di = s->di;
	unsigned int hash;
	vtx *vx;

	hash = (unsigned int)nix[MXPD+1];

	for (vx = s->vch[hash]; vx != NULL; vx = vx->chn) {
		for (e = 0; e <= di; e++) {
			if (nix[e] != vx->nix[e])
				break;
		}
		if (e > di) {
			return vx;
		}
	}
	return vx;
}
