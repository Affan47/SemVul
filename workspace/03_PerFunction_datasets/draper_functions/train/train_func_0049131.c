undo_panel_padding (DATASET *dset)
{
    char *mask = dset->padmask;
    double *Zi;
    char **S = NULL;
    int padded_n = dset->n;
    int real_n = dset->n;
    int i, t;
    int err = 0;

    for (t=0; t<dset->n; t++) {
	if (mask[t]) {
	    real_n--;
	}
    }

    fprintf(stderr, "undo_panel_padding: padded n*T = %d, original dset->n = %d\n",
	    padded_n, real_n);

    if (real_n == padded_n) {
	fprintf(stderr, "strange, couldn't find any padding!\n");
	return E_DATA;
    }


    Zi = malloc(real_n * sizeof *Zi);

    if (Zi == NULL) {
	return E_ALLOC;
    }

    if (dset->S != NULL) {

	S = strings_array_new_with_length(real_n, OBSLEN);
    }

    if (!err) {


	int s;

	for (i=0; i<dset->v; i++) {
	    s = 0;
	    for (t=0; t<padded_n; t++) {
		if (!mask[t]) {
		   Zi[s] = dset->Z[i][t];
		   if (i == 0 && S != NULL) {
		       strcpy(S[s], dset->S[t]);
		   }
		   s++;
		}
	    }

	    memcpy(dset->Z[i], Zi, real_n * sizeof *Zi);
	}

	if (dset->S != NULL && S != NULL) {
	    strings_array_free(dset->S, padded_n);
	    dset->S = S;
	}
    }

    free(Zi);

    dset->n = real_n;
    dset->t2 = dset->n - 1;
    free(dset->padmask);
    dset->padmask = NULL;

    return err;
}
