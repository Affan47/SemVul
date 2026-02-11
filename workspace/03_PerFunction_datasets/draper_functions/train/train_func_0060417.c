radeon_pm_reset_pad_ctlr_strength(struct radeonfb_info *rinfo)
{
	u32 tmp, tmp2;
	int i,j;


	INREG(PAD_CTLR_STRENGTH);
	OUTREG(PAD_CTLR_STRENGTH, INREG(PAD_CTLR_STRENGTH) & ~PAD_MANUAL_OVERRIDE);
	tmp = INREG(PAD_CTLR_STRENGTH);
	for (i = j = 0; i < 65; ++i) {
		mdelay(1);
		tmp2 = INREG(PAD_CTLR_STRENGTH);
		if (tmp != tmp2) {
			tmp = tmp2;
			i = 0;
			j++;
			if (j > 10) {
				printk(KERN_WARNING "radeon: PAD_CTLR_STRENGTH doesn't "
				       "stabilize !\n");
				break;
			}
		}
	}
}
