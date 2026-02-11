af9033_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct af9033_dev *dev = fe->demodulator_priv;
	struct dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	int ret, tmp, power_real;
	u8 u8tmp, gain_offset, buf[7];

	if (dev->is_af9035) {

		ret = af9033_rd_reg(dev, 0x800048, &u8tmp);
		if (ret < 0)
			goto err;


		*strength = u8tmp * 0xffff / 100;
	} else {
		ret = af9033_rd_reg(dev, 0x8000f7, &u8tmp);
		if (ret < 0)
			goto err;

		ret = af9033_rd_regs(dev, 0x80f900, buf, 7);
		if (ret < 0)
			goto err;

		if (c->frequency <= 300000000)
			gain_offset = 7;
		else
			gain_offset = 4;

		power_real = (u8tmp - 100 - gain_offset) -
			power_reference[((buf[3] >> 0) & 3)][((buf[6] >> 0) & 7)];

		if (power_real < -15)
			tmp = 0;
		else if ((power_real >= -15) && (power_real < 0))
			tmp = (2 * (power_real + 15)) / 3;
		else if ((power_real >= 0) && (power_real < 20))
			tmp = 4 * power_real + 10;
		else if ((power_real >= 20) && (power_real < 35))
			tmp = (2 * (power_real - 20)) / 3 + 90;
		else
			tmp = 100;


		*strength = tmp * 0xffff / 100;
	}

	return 0;

err:
	dev_dbg(&dev->client->dev, "failed=%d\n", ret);

	return ret;
}
