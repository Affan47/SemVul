compute_chisq (float *resid, float *weight, GMT_LONG nxy, double *chisq, double scale)
{
	GMT_LONG	i;
	double	tmp;

	*chisq = 0.0;
	for (i = 0; i < nxy; i++) {
		if (GMT_is_fnan (resid[i])) continue;
		tmp = resid[i];
		if (scale != 1.0) tmp /= scale;
		tmp *= tmp;
		if (weight[i] != 1.0) tmp *= weight[i];
		*chisq += tmp;
	}
	return;
}
