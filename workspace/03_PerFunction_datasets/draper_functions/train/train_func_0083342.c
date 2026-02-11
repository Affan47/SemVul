isl6423_set_current(struct dvb_frontend *fe)
{
	struct isl6423_dev *isl6423		= (struct isl6423_dev *) fe->sec_priv;
	u8 reg_3 = isl6423->reg_3;
	const struct isl6423_config *config	= isl6423->config;
	int err = 0;

	switch (config->current_max) {
	case SEC_CURRENT_275m:


		reg_3 &= ~0x3;
		break;

	case SEC_CURRENT_515m:


		reg_3 &= ~0x2;
		reg_3 |=  0x1;
		break;

	case SEC_CURRENT_635m:


		reg_3 &= ~0x1;
		reg_3 |=  0x2;
		break;

	case SEC_CURRENT_800m:


		reg_3 |= 0x3;
		break;
	}

	err = isl6423_write(isl6423, reg_3);
	if (err < 0)
		goto exit;

	switch (config->curlim) {
	case SEC_CURRENT_LIM_ON:

		reg_3 &= ~0x10;
		break;

	case SEC_CURRENT_LIM_OFF:

		reg_3 |= 0x10;
		break;
	}

	err = isl6423_write(isl6423, reg_3);
	if (err < 0)
		goto exit;

	isl6423->reg_3 = reg_3;

	return 0;
exit:
	dprintk(FE_ERROR, 1, "I/O error <%d>", err);
	return err;
}
