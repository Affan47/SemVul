matroxfb_g450_setpll_cond(struct matrox_fb_info *minfo, unsigned int mnp,
			       unsigned int pll)
{
	if (g450_cmppll(minfo, mnp, pll)) {
		g450_setpll(minfo, mnp, pll);
	}
}
