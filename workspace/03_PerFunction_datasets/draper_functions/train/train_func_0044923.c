dispwin_clone_ramdac(ramdac *r) {
	ramdac *nr;
	int i, j;

	debug("dispwin_clone_ramdac called\n");


	if ((nr = (ramdac *)calloc(sizeof(ramdac), 1)) == NULL) {
		return NULL;
	}

	*nr = *r;

	for (j = 0; j < 3; j++) {

		if ((nr->v[j] = (double *)calloc(sizeof(double), r->nent)) == NULL) {
			for (j--; j >= 0; j--)
				free(nr->v[j]);
			free(nr);
			return NULL;
		}
	}

	for (j = 0; j < 3; j++) {
		for (i = 0; i < r->nent; i++) {
			nr->v[j][i] = r->v[j][i];
		}
	}

	debug("clone is done\n");
	return nr;
}
