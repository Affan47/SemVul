mxl111sf_lgdt3305_frontend_attach(struct dvb_usb_adapter *adap, u8 fe_id)
{
	struct dvb_usb_device *d = adap_to_d(adap);
	struct mxl111sf_state *state = d_to_priv(d);
	struct mxl111sf_adap_state *adap_state = &state->adap_state[fe_id];
	int ret;

	pr_debug("%s()\n", __func__);


	state->d = d;
	adap_state->alt_mode = (dvb_usb_mxl111sf_isoc) ? 2 : 1;
	state->alt_mode = adap_state->alt_mode;

	if (usb_set_interface(d->udev, 0, state->alt_mode) < 0)
		pr_err("set interface failed");

	state->gpio_mode = MXL111SF_GPIO_MOD_ATSC;
	adap_state->gpio_mode = state->gpio_mode;
	adap_state->device_mode = MXL_TUNER_MODE;
	adap_state->ep6_clockphase = 1;

	ret = mxl1x1sf_soft_reset(state);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl111sf_init_tuner_demod(state);
	if (mxl_fail(ret))
		goto fail;

	ret = mxl1x1sf_set_device_mode(state, adap_state->device_mode);
	if (mxl_fail(ret))
		goto fail;

	ret = mxl111sf_enable_usb_output(state);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl1x1sf_top_master_ctrl(state, 1);
	if (mxl_fail(ret))
		goto fail;

	ret = mxl111sf_init_port_expander(state);
	if (mxl_fail(ret))
		goto fail;
	ret = mxl111sf_gpio_mode_switch(state, state->gpio_mode);
	if (mxl_fail(ret))
		goto fail;

	adap->fe[fe_id] = dvb_attach(lgdt3305_attach,
				 &hauppauge_lgdt3305_config,
				 &d->i2c_adap);
	if (adap->fe[fe_id]) {
		state->num_frontends++;
		adap_state->fe_init = adap->fe[fe_id]->ops.init;
		adap->fe[fe_id]->ops.init = mxl111sf_adap_fe_init;
		adap_state->fe_sleep = adap->fe[fe_id]->ops.sleep;
		adap->fe[fe_id]->ops.sleep = mxl111sf_adap_fe_sleep;
		return 0;
	}
	ret = -EIO;
fail:
	return ret;
}
