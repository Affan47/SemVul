texprint (MODEL *pmod, const DATASET *dset, char *fname,
	      gretlopt opt)
{
    PRN *prn;
    int eqn = (opt & OPT_E);
    int doc = (opt & OPT_O);
    int err = 0;

    if (RQ_SPECIAL_MODEL(pmod)) {
	return E_NOTIMP;
    }

    prn = make_tex_prn(pmod->ID, fname, eqn, doc, &err);

    if (!err) {
	err = tex_print_model(pmod, dset, opt, prn);
	gretl_print_destroy(prn);
    }

    return err;
}
