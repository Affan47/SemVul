compute_xcc(scanrd_ *s) {
	int i, n;
	double xcc = 0.0;

	if (s->xpt == 0)
		return 0;

	for (n = i = 0; i < s->nsbox; i++) {
		int e;
		sbox *sb = &s->sboxes[i];
		double Lab[3];


		for (e = 0; e < s->depth; e++) {
			sb->rot[s->crot].mP[e]  = sb->mP[e];
			sb->rot[s->crot].sdP[e] = sb->sdP[e];
			sb->rot[s->crot].P[e]   = sb->P[e];
		}
		sb->rot[s->crot].cnt = sb->cnt;

		if (sb->xpt[0] >= 0.0) {

			pval2Lab(Lab, sb->P, s->depth);


			for (e = 0; e < 3; e++) {
				double tt = Lab[e] - sb->xpt[e];
				xcc += tt * tt;
			}
			n++;
		}

	}
	xcc /= (double)n;


	s->rots[s->crot].xcc = xcc;

	return 0;
}
