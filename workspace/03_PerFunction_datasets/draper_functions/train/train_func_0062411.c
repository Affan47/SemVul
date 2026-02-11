clear_nlspec (nlspec *spec)
{
    int i;

    if (spec == NULL) {
	return;
    }

    free(spec->parnames);
    spec->parnames = NULL;

    if (spec->params != NULL) {
	for (i=0; i<spec->nparam; i++) {
	    free(spec->params[i].deriv);
	}
	free(spec->params);
	spec->params = NULL;
    }
    spec->nparam = 0;

    free(spec->fvec);
    spec->fvec = NULL;

    free(spec->jac);
    spec->jac = NULL;

    free(spec->coeff);
    spec->coeff = NULL;
    spec->ncoeff = 0;
    spec->nvec = 0;

    if (spec->aux != NULL) {
	for (i=0; i<spec->naux; i++) {
	    free(spec->aux[i]);
	}
	free(spec->aux);
	spec->aux = NULL;
    }
    spec->naux = 0;

    if (spec->genrs != NULL) {
	for (i=0; i<spec->ngenrs; i++) {
	    destroy_genr(spec->genrs[i]);
	}
	free(spec->genrs);
	spec->genrs = NULL;
    }
    spec->ngenrs = 0;
    spec->generr = 0;

    if (spec->hgen != NULL) {
	destroy_genr(spec->hgen);
	spec->hgen = NULL;
    }

    if (spec->hesscall != NULL) {
	free(spec->hesscall);
	spec->hesscall = NULL;
    }

    free(spec->nlfunc);
    spec->nlfunc = NULL;

    gretl_matrix_free(spec->Hinv);
    spec->Hinv = NULL;

    spec->flags = 0;
    spec->opt = OPT_NONE;

    spec->dv = 0;
    spec->lhtype = GRETL_TYPE_NONE;
    spec->lhv = 0;
    spec->lvec = NULL;

    spec->lhname[0] = '\0';
    spec->hname[0] = '\0';

    spec->iters = 0;
    spec->fncount = 0;
    spec->grcount = 0;

    spec->t1 = spec->t2 = 0;
    spec->real_t1 = spec->real_t2 = 0;
    spec->nobs = 0;

    spec->dset = NULL;
    spec->prn = NULL;

    if (spec->oc != NULL) {
	oc_set_destroy(spec->oc);
	spec->oc = NULL;
    }

    free(spec->missmask);
    spec->missmask = NULL;
}
