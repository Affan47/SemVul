gretl_model_unprotect (MODEL *pmod)
{
    MODEL **prmod;
    int match = 0;
    int i, j, err = 0;

    for (i=0; i<n_prot; i++) {
	if (protected_models[i] == pmod) {
	    match = 1;
	    for (j=i; j<n_prot-1; j++) {
		protected_models[j] = protected_models[j+1];
	    }
	    break;
	}
    }

    if (match) {
	if (n_prot == 1) {
	    free(protected_models);
	    protected_models = NULL;
	    n_prot = 0;
	} else {
	    prmod = realloc(protected_models, (n_prot - 1) * sizeof *prmod);
	    if (prmod == NULL) {
		fprintf(stderr, "gretl_model_unprotect: out of memory!\n");
		err = E_ALLOC;
	    } else {
		protected_models = prmod;
		n_prot--;
	    }
	}
    }

    return err;
}
