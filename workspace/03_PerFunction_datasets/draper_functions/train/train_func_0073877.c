aty_pll_to_var_ct(const struct fb_info *info, const union aty_pll *pll)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 ret;
	ret = par->ref_clk_per * pll->ct.pll_ref_div * pll->ct.vclk_post_div_real / pll->ct.vclk_fb_div / 2;
#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if(pll->ct.xres > 0) {
		ret *= par->lcd_width;
		ret /= pll->ct.xres;
	}
#endif
#ifdef DEBUG
	printk("atyfb(%s): calculated 0x%08X(%i)\n", __func__, ret, ret);
#endif
	return ret;
}
