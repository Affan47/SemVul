print_z_prob (double z, PRN *prn)
{
    double pv = NADBL;

    if (z > 0) {
	pv = normal_pvalue_1(z);
	if (!na(pv)) {
	    pprintf(prn, "  P(Z > %g) = %g\n", z, pv);
	}
    } else if (z < 0) {
	pv = normal_cdf(z);
	if (!na(pv)) {
	    pprintf(prn, "  P(Z < %g) = %g\n", z, pv);
	}
    }

    if (!na(pv) && pv > 0) {
	pprintf(prn, "  %s = %g\n", _("Two-tailed p-value"), 2 * pv);
    }

    return pv;
}
