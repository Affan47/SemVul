atyfb_blank(int blank, struct fb_info *info)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 gen_cntl;

	if (par->lock_blank || par->asleep)
		return 0;

#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table && blank > FB_BLANK_NORMAL &&
	    (aty_ld_lcd(LCD_GEN_CNTL, par) & LCD_ON)) {
		u32 pm = aty_ld_lcd(POWER_MANAGEMENT, par);
		pm &= ~PWR_BLON;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
	}
#endif

	gen_cntl = aty_ld_le32(CRTC_GEN_CNTL, par);
	gen_cntl &= ~0x400004c;
	switch (blank) {
	case FB_BLANK_UNBLANK:
		break;
	case FB_BLANK_NORMAL:
		gen_cntl |= 0x4000040;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		gen_cntl |= 0x4000048;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		gen_cntl |= 0x4000044;
		break;
	case FB_BLANK_POWERDOWN:
		gen_cntl |= 0x400004c;
		break;
	}
	aty_st_le32(CRTC_GEN_CNTL, gen_cntl, par);

#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table && blank <= FB_BLANK_NORMAL &&
	    (aty_ld_lcd(LCD_GEN_CNTL, par) & LCD_ON)) {
		u32 pm = aty_ld_lcd(POWER_MANAGEMENT, par);
		pm |= PWR_BLON;
		aty_st_lcd(POWER_MANAGEMENT, pm, par);
	}
#endif

	return 0;
}
