cyber2000fb_disable_extregs(struct cfb_info *cfb)
{
	if (cfb->func_use_count == 1) {
		int old;

		old = cyber2000_grphr(EXT_FUNC_CTL, cfb);
		old &= ~EXT_FUNC_CTL_EXTREGENBL;
		cyber2000_grphw(EXT_FUNC_CTL, old, cfb);
	}

	if (cfb->func_use_count == 0)
		printk(KERN_ERR "disable_extregs: count = 0\n");
	else
		cfb->func_use_count -= 1;
}
