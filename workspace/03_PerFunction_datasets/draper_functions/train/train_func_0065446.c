gretl_model_set_double (MODEL *pmod, const char *key, double val)
{
    double *valp;
    int err;


    valp = gretl_model_get_data(pmod, key);
    if (valp != NULL) {
	*valp = val;
	return 0;
    }

    valp = malloc(sizeof *valp);
    if (valp == NULL) return 1;

    *valp = val;

    err = gretl_model_set_data(pmod, key, valp, GRETL_TYPE_DOUBLE,
			       sizeof(double));
    if (err) free(valp);

    return err;
}
