nl_model_allocate (MODEL *pmod, nlspec *spec)
{
    int k = spec->ncoeff;
    int nvc = (k * k + k) / 2;

    pmod->vcv = NULL;

    pmod->coeff = malloc(k * sizeof *pmod->coeff);
    pmod->sderr = malloc(k * sizeof *pmod->sderr);

    if (pmod->coeff == NULL || pmod->sderr == NULL) {
	pmod->errcode = E_ALLOC;
	return pmod->errcode;
    }

    if (!(spec->opt & OPT_A)) {

	pmod->vcv = malloc(nvc * sizeof *pmod->vcv);
	if (pmod->vcv == NULL) {
	    pmod->errcode = E_ALLOC;
	}
    }

    if (pmod->errcode == 0) {
	pmod->ncoeff = k;
    }

    return pmod->errcode;
}
