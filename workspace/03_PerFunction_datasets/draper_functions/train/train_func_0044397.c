xc4000_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct i2c_adapter *tun_i2c;
	struct dib0700_adapter_state *state = adap->priv;


	tun_i2c = state->dib7000p_ops.get_i2c_master(adap->fe_adap[0].fe,
					  DIBX000_I2C_INTERFACE_TUNER, 1);
	if (tun_i2c == NULL) {
		printk(KERN_ERR "Could not reach tuner i2c bus\n");
		return 0;
	}


	adap->fe_adap[0].fe->callback = dib0700_xc4000_tuner_callback;

	return dvb_attach(xc4000_attach, adap->fe_adap[0].fe, tun_i2c,
			  &dib7000p_xc4000_tunerconfig)
		== NULL ? -ENODEV : 0;
}
