binomialTerm (gnm_float i, gnm_float j, gnm_float p, gnm_float q,
	      gnm_float diffFromMean, gboolean log_p)
{
	const gnm_float minLog1Value = -0.79149064;
	gnm_float c1,c2,c3;
	gnm_float c4,c5,c6,ps,logbinomialTerm,dfm;
	gnm_float t;

	if (i == 0 && j <= 0)
		return R_D__1;

	if (i <= -1 || j < 0)
		return R_D__0;

	c1 = (i + 1) + j;
	if (p < q) {
		c2 = i;
		c3 = j;
		ps = p;
		dfm = diffFromMean;
	} else {
		c3 = i;
		c2 = j;
		ps = q;
		dfm = -diffFromMean;
	}

	c5 = (dfm - (1 - ps)) / (c2 + 1);
	c6 = -(dfm + ps) / (c3 + 1);

	if (c5 < minLog1Value) {
		if (c2 == 0) {
			logbinomialTerm = c3 * gnm_log1p (-ps);
			return log_p ? logbinomialTerm : gnm_exp (logbinomialTerm);
		} else if (ps == 0 && c2 > 0) {
			return R_D__0;
		} else {
			t = gnm_log ((ps * c1) / (c2 + 1)) - c5;
		}
	} else {
		t = log1pmx (c5);
	}

	c4 = logfbit (i + j) - logfbit (i) - logfbit (j);
	logbinomialTerm = c4 + c2 * t - c5 + (c3 * log1pmx (c6) - c6);

	return log_p
		? logbinomialTerm + 0.5 * gnm_log (c1 / ((c2 + 1) * (c3 + 1) * 2 * M_PIgnum))
		: gnm_exp (logbinomialTerm) * gnm_sqrt (c1 / ((c2 + 1) * (c3 + 1) * 2 * M_PIgnum));
}
