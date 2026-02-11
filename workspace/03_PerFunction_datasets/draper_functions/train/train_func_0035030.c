get_coeff(int mclk, int rate)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].rate == rate && coeff_div[i].mclk == mclk)
			return i;
	}

	printk(KERN_ERR "wm8750: could not get coeff for mclk %d @ rate %d\n",
		mclk, rate);
	return -EINVAL;
}
