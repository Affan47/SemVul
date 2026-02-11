bcm3510_init(struct dvb_frontend* fe)
{
	struct bcm3510_state* st = fe->demodulator_priv;
	bcm3510_register_value j;
	struct bcm3510_hab_cmd_set_agc c;
	int ret;

	if ((ret = bcm3510_readB(st,0xca,&j)) < 0)
		return ret;

	deb_info("JDEC: %02x\n",j.raw);

	switch (j.JDEC_ca.JDEC) {
		case JDEC_WAIT_AT_RAM:
			deb_info("attempting to download firmware\n");
			if ((ret = bcm3510_init_cold(st)) < 0)
				return ret;
		case JDEC_EEPROM_LOAD_WAIT:
			deb_info("firmware is loaded\n");
			bcm3510_check_firmware_version(st);
			break;
		default:
			return -ENODEV;
	}

	memset(&c,0,1);
	c.SEL = 1;
	bcm3510_do_hab_cmd(st,CMD_AUTO_PARAM,MSGID_SET_RF_AGC_SEL,(u8 *)&c,sizeof(c),NULL,0);

	return 0;
}
