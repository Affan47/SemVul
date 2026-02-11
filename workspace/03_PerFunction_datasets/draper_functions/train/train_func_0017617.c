model_do_forecast (const char *str, MODEL *pmod,
			      DATASET *dset, gretlopt opt,
			      PRN *prn)
{
    char vname[VNAMELEN];
    FITRESID *fr;
    int t1, t2, k = -1;
    int err;

    if (pmod->ci == ARBOND || pmod->ci == DPANEL ||
	pmod->ci == HECKIT || pmod->ci == DURATION) {

	return E_NOTIMP;
    }

    if (pmod->ci == PANEL && !(pmod->opt & OPT_P)) {

	return E_NOTIMP;
    }

    if (pmod->ci == PROBIT && (pmod->opt & OPT_E)) {

	return E_NOTIMP;
    }


    if (gretl_model_get_int(pmod, "daily_repack")) {
	return E_DATA;
    }


    if (opt & OPT_I) {
	err = check_integrated_forecast_option(pmod, dset, NULL);
	if (err) {
	    return err;
	}
    }

    err = parse_forecast_string(str, opt, pmod->t2, dset,
				&t1, &t2, &k, vname);
    if (err) {
	return err;
    }

    if (*vname != '\0') {

	opt |= (OPT_A | OPT_Q);
    }

    if (opt & OPT_R) {
	fr = rolling_OLS_k_step_fcast(pmod, dset, t1, t2,
				      k, 0, &err);
    } else {
	fr = get_forecast(pmod, t1, t2, 0, dset, opt, &err);
    }

    if (!err && !(opt & OPT_Q)) {
	gretlopt printopt = opt;

	if (opt & OPT_U) {

	    printopt |= OPT_P;
	}
	err = text_print_forecast(fr, dset, printopt, prn);
    }

    if (!err && (opt & OPT_A)) {

	err = add_fcast_to_dataset(fr, vname, dset, prn);
    }

    if (!err) {
	set_forecast_matrices_from_fr(fr);
    }

    free_fit_resid(fr);

    return err;
}
