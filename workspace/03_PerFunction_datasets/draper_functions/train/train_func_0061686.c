aedsp16_hard_decode(void) {

	DBG((" aedsp16_hard_decode: 0x%x, 0x%x\n", hard_cfg[0], hard_cfg[1]));


	decoded_hcfg.iobase	= IOBASE(hard_cfg[0]);
	decoded_hcfg.joystick	= JOY(hard_cfg[0]);
	decoded_hcfg.wssbase	= WSSADDR(hard_cfg[0]);
	decoded_hcfg.mpubase	= MPUADDR(hard_cfg[0]);
	decoded_hcfg.cdrom	= CDROM(hard_cfg[1]);
	decoded_hcfg.cdrombase	= CDROMADDR(hard_cfg[1]);

#if defined(AEDSP16_INFO) || defined(AEDSP16_DEBUG)
	printk(" Original sound card configuration:\n");
	aedsp16_pinfo();
#endif


	decoded_hcfg.iobase	= ae_config.base_io;
	decoded_hcfg.wssbase	= ae_config.mss_base;
	decoded_hcfg.mpubase	= ae_config.mpu_base;

#if defined(CONFIG_SC6600_JOY)
 	decoded_hcfg.joystick	= CONFIG_SC6600_JOY;
#endif
#if defined(CONFIG_SC6600_CDROM)
	decoded_hcfg.cdrom	= CONFIG_SC6600_CDROM;
#endif
#if defined(CONFIG_SC6600_CDROMBASE)
	decoded_hcfg.cdrombase	= CONFIG_SC6600_CDROMBASE;
#endif

#if defined(AEDSP16_DEBUG)
	DBG((" New Values:\n"));
	aedsp16_pinfo();
#endif

	DBG(("success.\n"));
}
