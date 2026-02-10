gretl_coeff_vector_from_model (const MODEL *pmod, const char *select, int *err)
{
    gretl_vector *b;
    int i, j, nc;
    int k = pmod->ncoeff;

    if (select == NULL) {
	nc = k;
    } else {
	nc = count_selection(select, k);
    }

    if (nc == 0) {
	*err = E_DATA;
	return NULL;
    }

    b = gretl_column_vector_alloc(nc);
    if (b == NULL) {
	*err = E_ALLOC;
	return NULL;
    }

    j = 0;
    for (i=0; i<k; i++) {
	if (select != NULL && !select[i]) {
	    continue;
	}
	b->val[j++] = pmod->coeff[i];
    }

    return b;
}
