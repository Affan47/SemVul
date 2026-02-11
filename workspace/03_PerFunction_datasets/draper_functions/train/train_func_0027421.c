vecm_print_LR_test (GRETL_VAR *vecm, PRN *prn, int code)
{
    double ll0, x;
    int df;

    if (code == LR_RELATIVE) {
	ll0 = vecm->jinfo->prior_ll;
	df = vecm->jinfo->lrdf - vecm->jinfo->prior_df;
	gretl_prn_newline(prn);
	pputs(prn, A_("Relative to prior restriction"));
	pputc(prn, ':');
	gretl_prn_newline(prn);
    } else {
	ll0 = vecm->jinfo->ll0;
	df = vecm->jinfo->lrdf;
    }

    x = 2.0 * (ll0 - vecm->ll);

    if (tex_format(prn)) {
	pprintf(prn, A_("Unrestricted loglikelihood $(l_u) = %.8g$"), ll0);
	gretl_prn_newline(prn);
	pprintf(prn, A_("Restricted loglikelihood $(l_r) = %.8g$"), vecm->ll);
    } else {
	pprintf(prn, A_("Unrestricted loglikelihood (lu) = %.8g"), ll0);
	gretl_prn_newline(prn);
	pprintf(prn, A_("Restricted loglikelihood (lr) = %.8g"), vecm->ll);
    }

    gretl_prn_newline(prn);
    print_LR_stat(x, df, prn);
    gretl_prn_newline(prn);
}
