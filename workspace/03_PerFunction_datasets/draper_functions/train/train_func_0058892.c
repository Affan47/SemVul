tex_print_model (MODEL *pmod, const DATASET *dset,
		     gretlopt opt, PRN *prn)
{
    int err = 0;

    if (RQ_SPECIAL_MODEL(pmod)) {
	return E_NOTIMP;
    }

    if (tex_doc_format(prn)) {
	opt |= OPT_S;
    }

    if (tex_eqn_format(prn)) {
	err = tex_print_equation(pmod, dset, opt, prn);
    } else {
	if (opt & OPT_T) {

	    const char *s = get_optval_string(TABPRINT, OPT_T);

	    err = set_tex_param_format(s);
	}
	if (!err) {
	    err = printmodel(pmod, dset, OPT_NONE, prn);
	}
    }

    return err;
}
