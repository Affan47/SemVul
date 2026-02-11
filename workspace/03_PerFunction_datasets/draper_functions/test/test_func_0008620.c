q(double p, vector<double const *> const &par, bool lower,
	 bool log_p)
  const
{
    if (log_p)
	p = exp(p);

    if (!lower)
	p = 1 - p;

    if (p < 0.5) {
	return MU(par) - qexp(2 * (0.5 - p), SCALE(par), false, false);
    }
    else {
	return MU(par) + qexp(2 * (p - 0.5), SCALE(par), true, false);
    }
}
