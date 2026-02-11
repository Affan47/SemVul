pll_factors(struct pll_div *pll_div, unsigned int target,
		       unsigned int source, unsigned int mclk_div)
{
	u64 Kpart;
	unsigned long int K, Ndiv, Nmod, tmp;
	int i;


	for (i = 0; i < ARRAY_SIZE(post_table); i++) {
		tmp = target * post_table[i].div;
		if ((tmp >= 90000000 && tmp <= 100000000) &&
		    (mclk_div == post_table[i].mclkdiv)) {
			pll_div->freqmode = post_table[i].freqmode;
			pll_div->mclkdiv = post_table[i].mclkdiv;
			target *= post_table[i].div;
			break;
		}
	}

	if (i == ARRAY_SIZE(post_table)) {
		pr_err("%s: Unable to scale output frequency: %uHz\n",
		       __func__, target);
		return -EINVAL;
	}

	pll_div->prescale = 0;
	Ndiv = target / source;
	if (Ndiv < 5) {
		source >>= 1;
		pll_div->prescale = 1;
		Ndiv = target / source;
	}

	if (Ndiv < 5 || Ndiv > 13) {
		pr_err("%s: WM8804 N value is not within the recommended range: %lu\n",
		       __func__, Ndiv);
		return -EINVAL;
	}
	pll_div->n = Ndiv;

	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (u64)Nmod;

	do_div(Kpart, source);

	K = Kpart & 0xffffffff;
	if ((K % 10) >= 5)
		K += 5;
	K /= 10;
	pll_div->k = K;

	return 0;
}
