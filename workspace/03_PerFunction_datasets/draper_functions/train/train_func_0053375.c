lm_approximate (nlspec *spec, PRN *prn)
{
    int m = spec->nobs;
    int n = spec->ncoeff;
    int ldjac = m;
    int info = 0;
    int maxfev = 200 * (n + 1);
    int mode = 1, nprint = 0, nfev = 0;
    int iflag = 0;
    int *ipvt;
    double gtol = 0.0;
    double epsfcn = 0.0, factor = 100.;
    double *dspace, *diag, *qtf;
    double *wa1, *wa2, *wa3, *wa4;
    int err = 0;

    dspace = malloc((5 * n + m) * sizeof *dspace);
    ipvt = malloc(n * sizeof *ipvt);

    if (dspace == NULL || ipvt == NULL) {
	err = E_ALLOC;
	goto nls_cleanup;
    }

    diag = dspace;
    qtf = diag + n;
    wa1 = qtf + n;
    wa2 = wa1 + n;
    wa3 = wa2 + n;
    wa4 = wa3 + n;


    lmdif_(nls_calc_approx, m, n, spec->coeff, spec->fvec,
	   spec->tol, spec->tol, gtol, maxfev, epsfcn, diag,
	   mode, factor, nprint, &info, &nfev, spec->jac, ldjac,
	   ipvt, qtf, wa1, wa2, wa3, wa4, spec);

    spec->iters = nfev;

    switch ((int) info) {
    case -1:
	err = 1;
	break;
    case 0:
	gretl_errmsg_set(_("Invalid NLS specification"));
	err = 1;
	break;
    case 1:
    case 2:
    case 3:
    case 4:
	break;
    case 5:
    case 6:
    case 7:
    case 8:
	gretl_errmsg_sprintf(_("NLS: failed to converge after %d iterations"),
			     spec->iters);
	err = 1;
	break;
    default:
	break;
    }

    if (!err) {
	double ess = spec->crit;
	int iters = spec->iters;
	gretlopt opt = spec->opt;

	spec->opt = OPT_NONE;


	fdjac2_(nls_calc_approx, m, n, spec->coeff, spec->fvec,
		spec->jac, ldjac, &iflag, epsfcn, wa4, spec);
	spec->crit = ess;
	spec->iters = iters;
	spec->opt = opt;
    }

 nls_cleanup:

    free(dspace);
    free(ipvt);

    return err;
}
