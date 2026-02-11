hkl_lattice_reciprocal(HklLattice const *self, HklLattice *reciprocal)
{
	double c_alpha, c_beta, c_gamma;
	double s_alpha, s_beta, s_gamma;
	double c_beta1, c_beta2, c_beta3;
	double s_beta1, s_beta2, s_beta3;
	double s_beta_s_gamma, s_gamma_s_alpha, s_alpha_s_beta;
	double D;

	c_alpha = cos(self->alpha->value);
	c_beta  = cos(self->beta->value);
	c_gamma = cos(self->gamma->value);
	D = 1 - c_alpha*c_alpha - c_beta*c_beta - c_gamma*c_gamma
		+ 2*c_alpha*c_beta*c_gamma;

	if (D > 0.)
		D = sqrt(D);
	else
		return HKL_FAIL;

	s_alpha = sin(self->alpha->value);
	s_beta  = sin(self->beta->value);
	s_gamma = sin(self->gamma->value);

	s_beta_s_gamma  = s_beta  * s_gamma;
	s_gamma_s_alpha = s_gamma * s_alpha;
	s_alpha_s_beta  = s_alpha * s_beta;

	c_beta1 = (c_beta  * c_gamma - c_alpha) / s_beta_s_gamma;
	c_beta2 = (c_gamma * c_alpha - c_beta)  / s_gamma_s_alpha;
	c_beta3 = (c_alpha * c_beta  - c_gamma) / s_alpha_s_beta;
	s_beta1 = D / s_beta_s_gamma;
	s_beta2 = D / s_gamma_s_alpha;
	s_beta3 = D / s_alpha_s_beta;

	reciprocal->a->value = HKL_TAU * s_alpha / (self->a->value * D);
	reciprocal->b->value = HKL_TAU * s_beta  / (self->b->value * D);
	reciprocal->c->value = HKL_TAU * s_gamma / (self->c->value * D);
	reciprocal->alpha->value = atan2(s_beta1, c_beta1);
	reciprocal->beta->value  = atan2(s_beta2, c_beta2);
	reciprocal->gamma->value = atan2(s_beta3, c_beta3);

	return HKL_SUCCESS;
}
