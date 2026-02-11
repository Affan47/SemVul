real_nonlinearity_test (MODEL *pmod, int *list,
			DATASET *dset, int aux_code,
			gretlopt opt, PRN *prn)
{
    MODEL aux;
    int err;

    err = add_residual_to_dataset(pmod, dset);
    if (err) {
	return err;
    }


    list[1] = dset->v - 1;

    aux = lsq(list, dset, OLS, OPT_A);
    if (aux.errcode) {
	err = aux.errcode;
	fprintf(stderr, "auxiliary regression failed\n");
    } else {
	double pval, trsq = aux.rsq * aux.nobs;
	int df = aux.ncoeff - pmod->ncoeff;

	if (df <= 0) {

	    err = E_SINGULAR;
	    goto bailout;
	}

	pval = chisq_cdf_comp(df, trsq);

	aux.aux = aux_code;

	if (opt & OPT_Q) {
	    nonlin_test_header(aux_code, prn);
	} else {
	    printmodel(&aux, dset, opt, prn);
	    pputc(prn, '\n');
	}

	pprintf(prn, "  %s: TR^2 = %g,\n  ", _("Test statistic"), trsq);
	pprintf(prn, "%s = P(%s(%d) > %g) = %g\n\n",
		_("with p-value"), _("Chi-square"), df, trsq, pval);

	if (opt & OPT_S) {
	    ModelTest *test;

	    test = model_test_new((aux_code == AUX_SQ)?
				  GRETL_TEST_SQUARES : GRETL_TEST_LOGS);
	    if (test != NULL) {
		model_test_set_teststat(test, GRETL_STAT_LM);
		model_test_set_dfn(test, df);
		model_test_set_value(test, trsq);
		model_test_set_pvalue(test, chisq_cdf_comp(df, trsq));
		maybe_add_test_to_model(pmod, test);
	    }
	}

	record_test_result(trsq, pval, _("non-linearity"));
    }

 bailout:

    clear_model(&aux);

    return err;
}
