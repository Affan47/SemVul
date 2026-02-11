tua9001_set_params(struct dvb_frontend *fe)
{
	struct tua9001_dev *dev = fe->tuner_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, i;
	u16 val;
	struct tua9001_reg_val data[2];

	dev_dbg(&client->dev,
		"delivery_system=%u frequency=%u bandwidth_hz=%u\n",
		c->delivery_system, c->frequency, c->bandwidth_hz);

	switch (c->delivery_system) {
	case SYS_DVBT:
		switch (c->bandwidth_hz) {
		case 8000000:
			val  = 0x0000;
			break;
		case 7000000:
			val  = 0x1000;
			break;
		case 6000000:
			val  = 0x2000;
			break;
		case 5000000:
			val  = 0x3000;
			break;
		default:
			ret = -EINVAL;
			goto err;
		}
		break;
	default:
		ret = -EINVAL;
		goto err;
	}

	data[0].reg = 0x04;
	data[0].val = val;
	data[1].reg = 0x1f;
	data[1].val = div_u64((u64) (c->frequency - 150000000) * 48, 1000000);

	if (fe->callback) {
		ret = fe->callback(client->adapter,
				   DVB_FRONTEND_COMPONENT_TUNER,
				   TUA9001_CMD_RXEN, 0);
		if (ret)
			goto err;
	}

	for (i = 0; i < ARRAY_SIZE(data); i++) {
		ret = regmap_write(dev->regmap, data[i].reg, data[i].val);
		if (ret)
			goto err;
	}

	if (fe->callback) {
		ret = fe->callback(client->adapter,
				   DVB_FRONTEND_COMPONENT_TUNER,
				   TUA9001_CMD_RXEN, 1);
		if (ret)
			goto err;
	}
	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}
