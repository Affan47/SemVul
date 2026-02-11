gretl_model_set_coeff_separator (MODEL *pmod, const char *s, int pos)
{
    CoeffSep *cs = malloc(sizeof *cs);
    int err = 0;

    if (cs == NULL) {
	return E_ALLOC;
    }

    cs->str[0] = '\0';
    if (s != NULL) {
	strncat(cs->str, s, CSLEN - 1);
    }
    cs->pos = pos;

    err = gretl_model_set_data(pmod, "coeffsep", cs, GRETL_TYPE_STRUCT,
			       sizeof *cs);
    if (err) {
	free(cs);
    }

    return err;
}
