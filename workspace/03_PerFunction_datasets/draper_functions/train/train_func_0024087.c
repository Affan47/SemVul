mxl111sf_init(struct dvb_usb_device *d)
{
	struct mxl111sf_state *state = d_to_priv(d);
	int ret;
	static u8 eeprom[256];
	struct i2c_client c;

	ret = get_chip_info(state);
	if (mxl_fail(ret))
		pr_err("failed to get chip info during probe");

	mutex_init(&state->fe_lock);

	if (state->chip_rev > MXL111SF_V6)
		mxl111sf_config_pin_mux_modes(state, PIN_MUX_TS_SPI_IN_MODE_1);

	c.adapter = &d->i2c_adap;
	c.addr = 0xa0 >> 1;

	ret = tveeprom_read(&c, eeprom, sizeof(eeprom));
	if (mxl_fail(ret))
		return 0;
	tveeprom_hauppauge_analog(&c, &state->tv, (0x84 == eeprom[0xa0]) ?
			eeprom + 0xa0 : eeprom + 0x80);
#if 0
	switch (state->tv.model) {
	case 117001:
	case 126001:
	case 138001:
		break;
	default:
		printk(KERN_WARNING "%s: warning: "
		       "unknown hauppauge model #%d\n",
		       __func__, state->tv.model);
	}
#endif
	return 0;
}
