getprob(char *n)
{
	unsigned long	ngood, nbad;
	unsigned	g, b;
	float	p, BOT, TOP;

	ngood = getn(&super[OF_super_ngood]);
	nbad = getn(&super[OF_super_nbad]);
	if (ngood + nbad >= 18000) {
		BOT = .0001;
		TOP = .9999;
	} else if (ngood + nbad >= 9000) {
		BOT = .001;
		TOP = .999;
	} else {
		BOT = .01;
		TOP = .99;
	}
	g = get(&n[OF_node_good]) * 2;
	b = get(&n[OF_node_bad]);
	if (g + b >= 5) {
		p = smin(1.0, nbad ? (float)b/nbad : 0.0) /
			(smin(1.0, ngood ? (float)g/ngood : 0.0) +
			 smin(1.0, nbad ? (float)b/nbad : 0.0));
		p = smin(TOP, p);
		p = smax(BOT, p);
		if (p == TOP && b <= 10 && g == 0)
			p -= BOT;
		else if (p == BOT && g <= 10 && b == 0)
			p += BOT;
	} else if (g == 0 && b == 0)
		p = DFL;
	else
		p = 0;
	return p;
}
