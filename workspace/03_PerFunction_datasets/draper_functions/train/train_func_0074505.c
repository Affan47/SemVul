arch_test_print_simple (int order, double LM,
				    double pval, gretlopt opt,
				    PRN *prn)
{
    if (opt & OPT_M) {

	pprintf(prn, "%s: TR^2 = %f,\n", _("Test statistic"), LM);
    } else {
	pprintf(prn, "\n%s %d\n", _("Test for ARCH of order"), order);
	pprintf(prn, "\n%s: TR^2 = %f,\n", _("Test statistic"), LM);
    }
    pprintf(prn, "%s = P(%s(%d) > %f) = %f\n\n",
	    _("with p-value"), _("Chi-square"),
	    order, LM, pval);
}
