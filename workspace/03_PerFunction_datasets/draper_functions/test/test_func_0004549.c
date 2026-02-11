adf_test (int order, const int *list, DATASET *dset,
	      gretlopt opt, PRN *prn)
{
    int save_t1 = dset->t1;
    int save_t2 = dset->t2;
    int panelmode;
    int err;


    err = incompatible_options(opt, OPT_N | OPT_R | OPT_G);
    if (!err) {
	err = incompatible_options(opt, OPT_D | OPT_G);
    }

    if (!err && (opt & OPT_G)) {

	err = incompatible_options(opt, OPT_C | OPT_T);
    }

    panelmode = multi_unit_panel_sample(dset);

    if (panelmode) {
	err = panel_DF_test(list[1], order, dset, opt, prn);
    } else {

	int i, v, vlist[2] = {1, 0};

	for (i=1; i<=list[0] && !err; i++) {
	    vlist[1] = v = list[i];
	    err = list_adjust_sample(vlist, &dset->t1, &dset->t2, dset, NULL);
	    if (!err && order == -1) {


		int T = dset->t2 - dset->t1 + 1;

		order = 12.0 * pow(T/100.0, 0.25);
	    }
	    if (!err) {
		err = real_adf_test(v, order, 1, dset, opt,
				    0, NULL, prn);
	    }
	    dset->t1 = save_t1;
	    dset->t2 = save_t2;
	}
    }

    dset->t1 = save_t1;
    dset->t2 = save_t2;

    return err;
}
