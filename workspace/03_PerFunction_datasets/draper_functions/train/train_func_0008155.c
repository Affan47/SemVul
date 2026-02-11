aty_valid_pll_ct(const struct fb_info *info, u32 vclk_per, struct pll_ct *pll)
{
	u32 q;
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	int pllvclk;


	q = par->ref_clk_per * pll->pll_ref_div * 4 / vclk_per;
	if (q < 16*8 || q > 255*8) {
		printk(KERN_CRIT "atyfb: vclk out of range\n");
		return -EINVAL;
	} else {
		pll->vclk_post_div  = (q < 128*8);
		pll->vclk_post_div += (q <  64*8);
		pll->vclk_post_div += (q <  32*8);
	}
	pll->vclk_post_div_real = postdividers[pll->vclk_post_div];

	pll->vclk_fb_div = q * pll->vclk_post_div_real / 8;
	pllvclk = (1000000 * 2 * pll->vclk_fb_div) /
		(par->ref_clk_per * pll->pll_ref_div);
#ifdef DEBUG
	printk("atyfb(%s): pllvclk=%d MHz, vclk=%d MHz\n",
		__func__, pllvclk, pllvclk / pll->vclk_post_div_real);
#endif
	pll->pll_vclk_cntl = 0x03;


	if (par->pll_limits.ecp_max) {
		int ecp = pllvclk / pll->vclk_post_div_real;
		int ecp_div = 0;

		while (ecp > par->pll_limits.ecp_max && ecp_div < 2) {
			ecp >>= 1;
			ecp_div++;
		}
		pll->pll_vclk_cntl |= ecp_div << 4;
	}

	return 0;
}
