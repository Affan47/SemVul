qf (gnm_float p, gnm_float n1, gnm_float n2, gboolean lower_tail, gboolean log_p)
{
	gnm_float q, qc;
#ifdef IEEE_754
	if (gnm_isnan(p) || gnm_isnan(n1) || gnm_isnan(n2))
		return p + n1 + n2;
#endif
	if (n1 <= 0. || n2 <= 0.) ML_ERR_return_NAN;

	R_Q_P01_check(p);
	if (p == R_DT_0)
		return 0;

	q = qbeta (p, n2 / 2, n1 / 2, !lower_tail, log_p);
	if (q < 0.9)
		qc = 1 - q;
	else
		qc = qbeta (p, n1 / 2, n2 / 2, lower_tail, log_p);

	return (qc / q) * (n2 / n1);
}
