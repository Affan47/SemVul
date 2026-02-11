gretl_VAR_print_all_fcast_decomps (GRETL_VAR *var, const DATASET *dset,
				       int horizon, PRN *prn)
{
    int i, err = 0;

    if (horizon <= 0) {
	horizon = default_VAR_horizon(dset);
    }

    if (rtf_format(prn)) {
	pputs(prn, "{\\rtf1\\par\n\\qc ");
    }

    for (i=0; i<var->neqns && !err; i++) {
	err = gretl_VAR_print_fcast_decomp(var, i, horizon, dset,
					   prn);
    }

    if (rtf_format(prn)) {
	pputs(prn, "}\n");
    }

    return err;
}
