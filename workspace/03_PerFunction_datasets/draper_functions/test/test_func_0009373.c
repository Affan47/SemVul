pll_factors(struct pll_ *pll_div,
			unsigned int target, unsigned int source)
{
	unsigned long long Kpart;
	unsigned int K, Ndiv, Nmod;


	target *= 4;

	Ndiv = target / source;
	if (Ndiv < 6) {
		source /= 2;
		pll_div->pre_div = 1;
		Ndiv = target / source;
	} else
		pll_div->pre_div = 0;

	if ((Ndiv < 6) || (Ndiv > 12))
		printk(KERN_WARNING
			"WM8974 N value %u outwith recommended range!\n",
			Ndiv);

	pll_div->n = Ndiv;
	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (long long)Nmod;

	do_div(Kpart, source);

	K = Kpart & 0xFFFFFFFF;


	if ((K % 10) >= 5)
		K += 5;


	K /= 10;

	pll_div->k = K;
}
