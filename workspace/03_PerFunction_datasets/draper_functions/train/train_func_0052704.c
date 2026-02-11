get_x_sorted_order (const FITRESID *fr,
				const double *x,
				int t1, int *pt2)
{
    int *order = NULL;
    struct fsorter *fs;
    int nmiss = 0;
    int t2 = *pt2;
    int n = t2 - t1 + 1;
    int i, t;

    for (t=t1; t<=t2; t++) {
	if (na(fr->actual[t])) {
	    nmiss++;
	}
    }

    fs = malloc(n * sizeof *fs);
    if (fs == NULL) {
	return NULL;
    }

    order = malloc(n * sizeof *order);
    if (order == NULL) {
	free(fs);
	return NULL;
    }

    for (i=0, t=t1; t<=t2; t++, i++) {
	fs[i].obs = t;
	fs[i].y = x[t];
    }

    qsort(fs, n, sizeof *fs, compare_fs);

    for (i=0; i<n; i++) {
	order[i] = fs[i].obs;
    }

    free(fs);

    if (nmiss > 0) {

	*pt2 = (n - nmiss) + t1 - 1;
    }

    return order;
}
