johansen_driver (GRETL_VAR *jvar,
		 gretl_restriction *rset,
		 const DATASET *dset,
		 gretlopt opt, PRN *prn)
{
    int r = jrank(jvar);

    if (r == 0) {

	coint_test_header(jvar, dset, prn);
    }

    jvar->err = johansen_stage_1(jvar, dset, opt, prn);
    if (jvar->err) {
	return jvar->err;
    }

    if (opt & OPT_V) {
	print_johansen_sigmas(jvar->jinfo, prn);
    }

    if (r > 0) {

	jvar->err = jvar_check_allocation(jvar, dset);
    }

    if (!jvar->err) {

	if (r > 0) {
	    jvar->err = johansen_estimate_complete(jvar, rset, dset,
						   prn);
	} else {
	    jvar->err = johansen_test_complete(jvar, dset, opt, prn);
	}
    }

    return jvar->err;
}
