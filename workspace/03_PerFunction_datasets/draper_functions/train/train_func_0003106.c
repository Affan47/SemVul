q(double p, vector<double const *> const &par, bool lower,
	   bool log_p) const
{
    if (SIZE(par) == 0) {
	return 0;
    }
    else {
	return qnbinom(p, SIZE(par), PROB(par), lower, log_p);
    }
}
