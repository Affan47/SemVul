ordered_model (const MODEL *pmod)
{
    if (pmod->ci == PROBIT || pmod->ci == LOGIT) {
	if (gretl_model_get_int(pmod, "ordered")) {
	    return 1;
	}
    }

    return 0;
}
