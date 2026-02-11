stk807xpvr_frontend_attach0(struct dvb_usb_adapter *adap)
{
	struct dib0700_adapter_state *state = adap->priv;

	if (!dvb_attach(dib8000_attach, &state->dib8000_ops))
		return -ENODEV;

	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(500);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_clock(adap->dev, 72, 1);

	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);


	state->dib8000_ops.i2c_enumeration(&adap->dev->i2c_adap, 1, 0x22, 0x80, 0);

	adap->fe_adap[0].fe = state->dib8000_ops.init(&adap->dev->i2c_adap, 0x80,
			      &dib807x_dib8000_config[0]);

	return adap->fe_adap[0].fe == NULL ? -ENODEV : 0;
}
