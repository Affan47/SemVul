compatible(
gamut *s, struct _gamut *t) {
	int j;


	if ((s->isJab && !t->isJab)
	 || (!s->isJab && t->isJab)) {
		return 0;
	}


	for (j = 0; j < 3; j++) {
		if (fabs(s->cent[j] - t->cent[j]) > 1e-9) {
			return 0;
		}
	}
	return 1;
}
