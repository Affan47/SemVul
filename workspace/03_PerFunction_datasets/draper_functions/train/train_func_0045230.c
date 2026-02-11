spearman_rho (const int *list, const DATASET *dset,
		  gretlopt opt, PRN *prn)
{
    int T = dset->t2 - dset->t1 + 1;
    double *rx = NULL, *ry = NULL;
    const double *x, *y;
    double rho, zval;
    int vx, vy, m;
    int err;

    if (list[0] != 2) {
	pputs(prn, _("This command requires two variables\n"));
	return 1;
    }

    vx = list[1];
    vy = list[2];

    x = dset->Z[vx] + dset->t1;
    y = dset->Z[vy] + dset->t1;

    err = real_spearman_rho(x, y, T, &rho, &zval,
			    (opt & OPT_V)? &rx : NULL,
			    (opt & OPT_V)? &ry : NULL,
			    &m);
    if (err) {
	return err;
    }

    pprintf(prn, _("\nFor the variables '%s' and '%s'\n"), dset->varname[vx],
	    dset->varname[vy]);

    if (na(rho)) {
	pputs(prn, _("Spearman's rank correlation is undefined\n"));
	return err;
    }

    pprintf(prn, _("Spearman's rank correlation coefficient (rho) = %.8f\n"), rho);

    if (rho == 0.0) {
	goto skipit;
    }

    if (!na(zval)) {
	pputs(prn, _("Under the null hypothesis of no correlation:\n "));
	pprintf(prn, _("z-score = %g, with two-tailed p-value %.4f\n"), zval,
		normal_pvalue_2(zval));
    } else if (m > 24) {
	double tval = rho * sqrt((m - 2) / (1 - rho*rho));

	pputs(prn, _("Under the null hypothesis of no correlation:\n "));
	pprintf(prn, _("t(%d) = %g, with two-tailed p-value %.4f\n"), m - 2,
		tval, student_pvalue_2(m - 2, tval));
    } else if (m >= 7) {
	double pval = spearman_signif(fabs(rho), m);

	if (pval < 1.0) {
	    pprintf(prn, _("significant at the %g%% level (two-tailed)\n"),
		    100.0 * pval);
	} else {

	    pputs(prn, _("not significant at the 10% level\n"));
	}
    } else {
	pputs(prn, _("Sample is too small to calculate a p-value based on "
		     "the normal distribution\n"));
    }

 skipit:

    if (rx != NULL && ry != NULL) {
	print_raw_and_ranked(vx, vy, x, y, rx, ry, dset, prn);
	free(rx);
	free(ry);
    }

    pputc(prn, '\n');

    return 0;
}
