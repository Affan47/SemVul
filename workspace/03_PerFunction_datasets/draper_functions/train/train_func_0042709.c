GMT_Fcrit (double alpha, double nu1, double nu2)
{


	GMT_LONG NU1, NU2;
	GMT_LONG done;
	double F_low, F_high, F_mid, p_high, p_mid, p, chisq1, chisq2;
	void F_to_ch1_ch2 (double F, double nu1, double nu2, double *chisq1, double *chisq2);

	F_high = 5.0;
	p = 1.0 - alpha;
	F_low = 0.0;
	F_to_ch1_ch2 (F_high, nu1, nu2, &chisq1, &chisq2);
	NU1 = (GMT_LONG)irint (nu1);
	NU2 = (GMT_LONG)irint (nu2);
	GMT_f_q (chisq1, NU1, chisq2, NU2, &p_high);
	while (p_high > p) {
		F_high *= 2.0;
		F_to_ch1_ch2 (F_high, nu1, nu2, &chisq1, &chisq2);
		GMT_f_q (chisq1, NU1, chisq2, NU2, &p_high);
	}


	done = FALSE;
	while (!done) {
		F_mid = 0.5 * (F_low + F_high);
		F_to_ch1_ch2 (F_mid, nu1, nu2, &chisq1, &chisq2);
		GMT_f_q (chisq1, NU1, chisq2, NU2, &p_mid);
		if (GMT_IS_ZERO (p_mid - p)) {
			done = TRUE;
		}
		else if (p_mid < p) {
			F_high = F_mid;
		}
		else {
			F_low = F_mid;
		}
	}
	return (F_mid);
}
