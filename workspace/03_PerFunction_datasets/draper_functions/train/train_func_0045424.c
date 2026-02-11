model_get_intervals_matrix (const MODEL *pmod, int *err)
{
    gretl_matrix *m, *ci;

    ci = gretl_model_get_data(pmod, "coeff_intervals");
    if (ci == NULL) {
	*err = E_BADSTAT;
	return NULL;
    }

    m = gretl_matrix_copy(ci);

    if (m == NULL) {
	*err = E_ALLOC;
    }

    return m;
}
