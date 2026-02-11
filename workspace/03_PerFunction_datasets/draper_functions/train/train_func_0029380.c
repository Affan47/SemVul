gretl_normality_test (int varno, const DATASET *dset,
			  gretlopt opt, PRN *prn)
{
    gretlopt alltests = OPT_D | OPT_W | OPT_J | OPT_L;
    double test = NADBL;
    double pval = NADBL;
    double trec = NADBL;
    double pvrec = NADBL;
    int err;

    if (varno < 0 || varno >= dset->v) {
	return E_DATA;
    }

    err = incompatible_options(opt, OPT_A | alltests);
    if (err) {
	return err;
    }

    if (opt & OPT_A) {

	opt |= alltests;
    }

    if (!(opt & alltests)) {

	opt |= OPT_D;
    }

    if (!(opt & OPT_Q)) {
	pprintf(prn, _("Test for normality of %s:"), dset->varname[varno]);
	if (opt & OPT_A) {
	    pputs(prn, "\n\n");
	} else {
	    pputc(prn, '\n');
	}
    }

    if (opt & OPT_D) {
	err = skew_kurt_test(dset->Z[varno], dset->t1, dset->t2,
			     &test, &pval, OPT_D);
	if (!err && !(opt & OPT_Q)) {
	    print_normality_stat(test, pval, OPT_D, prn);
	}
	if (!err) {

	    trec = test;
	    pvrec = pval;
	}
    }

    if (opt & OPT_W) {
	err = shapiro_wilk(dset->Z[varno], dset->t1, dset->t2,
			   &test, &pval);
	if (!err && !(opt & OPT_Q)) {
	    print_normality_stat(test, pval, OPT_W, prn);
	}
    }

    if (opt & OPT_L) {
	err = lilliefors_test(dset->Z[varno], dset->t1, dset->t2,
			      &test, &pval);
	if (!err && !(opt & OPT_Q)) {
	    print_normality_stat(test, pval, OPT_L, prn);
	}
    }

    if (opt & OPT_J) {
	err = skew_kurt_test(dset->Z[varno], dset->t1, dset->t2,
			     &test, &pval, OPT_J);
	if (!err && !(opt & OPT_Q)) {
	    print_normality_stat(test, pval, OPT_J, prn);
	}
    }

    if (na(trec) && !na(test)) {
	trec = test;
    }

    if (na(pvrec) && !na(pval)) {
	pvrec = pval;
    }

    if (!na(trec) && !na(pvrec)) {
	record_test_result(trec, pvrec, "Normality");
    }

    return err;
}
