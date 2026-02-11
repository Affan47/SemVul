gretl_system_residual_mplot (void *p, int ci, const DATASET *dset)
{
    const gretl_matrix *E = NULL;
    GRETL_VAR *var = NULL;
    equation_system *sys = NULL;
    FILE *fp = NULL;
    const double *obs;
    double startdate;
    double xmin, xmax, xrange;
    int nvars, nobs, jump;
    int i, v, t, t1;
    int err = 0;

    if (ci == VAR || ci == VECM) {
	var = (GRETL_VAR *) p;
	E = gretl_VAR_get_residual_matrix(var);
    } else if (ci == SYSTEM) {
	sys = (equation_system *) p;
	E = sys->E;
    }

    if (E == NULL) {
	return E_DATA;
    }

    nvars = gretl_matrix_cols(E);
    if (nvars > 6) {
	return 1;
    }

    obs = gretl_plotx(dset, OPT_NONE);
    if (obs == NULL) {
	return E_ALLOC;
    }

    nobs = gretl_matrix_rows(E);
    t1 = gretl_matrix_get_t1(E);

    fp = open_plot_input_file(PLOT_MULTI_SCATTER, &err);
    if (err) {
	return err;
    }

    fprintf(fp, "set multiplot layout %d,1\n", nvars);
    fputs("set nokey\n", fp);
    fputs("set xzeroaxis\n", fp);
    fputs("set noxlabel\n", fp);
    fputs("set noylabel\n", fp);

    gretl_push_c_numeric_locale();

    startdate = obs[t1];
    jump = nobs / (2 * dset->pd);
    fprintf(fp, "set xtics %g, %d\n", ceil(startdate), jump);

    gretl_minmax(t1, t1 + nobs - 1, obs, &xmin, &xmax);
    xrange = xmax - xmin;
    xmin -= xrange * .025;
    xmax += xrange * .025;
    fprintf(fp, "set xrange [%.10g:%.10g]\n", xmin, xmax);

    for (i=0; i<nvars; i++) {
	if (var != NULL) {
	    v = gretl_VAR_get_variable_number(var, i);
	} else {
	    v = system_get_depvar(sys, i);
	}

	fprintf(fp, "set title '%s'\n", dset->varname[v]);
	fputs("plot '-' using 1:2 with lines\n", fp);

	for (t=0; t<nobs; t++) {
	    double eti;

	    fprintf(fp, "%.10g\t", obs[t+t1]);
	    eti = gretl_matrix_get(E, t, i);
	    if (na(eti)) {
		fputs("?\n", fp);
	    } else {
		fprintf(fp, "%.10g\n", eti);
	    }
	}
	fputs("e\n", fp);
    }

    gretl_pop_c_numeric_locale();
    fputs("unset multiplot\n", fp);

    return finalize_plot_input_file(fp);
}
