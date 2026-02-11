calc_timeout(struct taia *then, struct taia *now)
{
	double d;
	struct taia tmp;
	if (taia_less (then, now))
		return 0;
	taia_sub (&tmp, then, now);
	d = taia_approx (&tmp);
	if (d > 1000.0)
		d = 1000.0;
	return d * 1000.0 + 20.0;
}
