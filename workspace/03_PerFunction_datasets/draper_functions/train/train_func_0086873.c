do_isostasy (double *par)
{


	GMT_LONG	k;
	double	airy_ratio, rigidity_d, d_over_restoring_force, mk, k2, k4, transfer_fn;

	double	te;
	double	rl;
	double	rm;
	double	rw;
	double	ri;

	double	youngs_modulus = 1.0e11;
	double	normal_gravity = 9.80619203;
	double	poissons_ratio = 0.25;

	te = par[0];	rl = par[1];	rm = par[2];	rw = par[3];	ri = par[4];
	rigidity_d = (youngs_modulus * te * te * te) / (12.0 * (1.0 - poissons_ratio * poissons_ratio));
	d_over_restoring_force = rigidity_d / ( (rm - ri) * normal_gravity);
	airy_ratio = -(rl - rw)/(rm - ri);

	if (te == 0.0) {
		scale_out *= airy_ratio;
		return;
	}

	for (k = 0; k < ndatac; k+= 2) {
		mk = modk(k);
		k2 = mk * mk;
		k4 = k2 * k2;
		transfer_fn = airy_ratio / ( (d_over_restoring_force * k4) + 1.0);
		datac[k] *= (float)transfer_fn;
		datac[k+1] *= (float)transfer_fn;
	}
}
