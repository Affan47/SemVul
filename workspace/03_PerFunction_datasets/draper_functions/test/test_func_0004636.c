bcm3510_init_cold(struct bcm3510_state *st)
{
	int ret;
	bcm3510_register_value v;


	if ((ret = bcm3510_readB(st,0xa2,&v)) < 0)
		return ret;
	if (v.APSTAT1_a2.RUN) {
		deb_info("AP is already running - firmware already loaded.\n");
		return 0;
	}

	deb_info("reset?\n");
	if ((ret = bcm3510_reset(st)) < 0)
		return ret;

	deb_info("tristate?\n");

	v.TSTCTL_2e.CTL = 0;
	if ((ret = bcm3510_writeB(st,0x2e,v)) < 0)
		return ret;

	deb_info("firmware?\n");
	if ((ret = bcm3510_download_firmware(&st->frontend)) < 0 ||
		(ret = bcm3510_clear_reset(st)) < 0)
		return ret;


	return 0;
}
