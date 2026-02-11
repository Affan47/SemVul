print_whites_test (double LM, int df, double pval,
			       gretlopt opt, PRN *prn)
{
    if (opt & OPT_B) {
	pprintf(prn, "\n%s\n", _("Breusch-Pagan test for heteroskedasticity"));
	if (opt & OPT_R) {
	    pprintf(prn, "%s\n", _("with Koenker robust variance estimator"));
	}
	pprintf(prn, "\n%s: LM = %f,\n", _("Test statistic"), LM);
    } else {
	pprintf(prn, "\n%s", _("White's test for heteroskedasticity"));
	if (opt & OPT_X) {
	    pprintf(prn, " (%s)\n", _("squares only"));
	} else {
	    pputc(prn, '\n');
	}
	pprintf(prn, "\n%s: TR^2 = %f,\n", _("Test statistic"), LM);
    }

    pprintf(prn, "%s = P(%s(%d) > %f) = %f\n\n",
	    _("with p-value"), _("Chi-square"),
	    df, LM, pval);
}
