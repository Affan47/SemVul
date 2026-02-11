af9035_tuner_detach(struct dvb_usb_adapter *adap)
{
	struct state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);

	dev_dbg(&d->udev->dev, "%s: adap->id=%d\n", __func__, adap->id);

	switch (state->af9033_config[adap->id].tuner) {
	case AF9033_TUNER_TUA9001:
	case AF9033_TUNER_FC2580:
	case AF9033_TUNER_IT9135_38:
	case AF9033_TUNER_IT9135_51:
	case AF9033_TUNER_IT9135_52:
	case AF9033_TUNER_IT9135_60:
	case AF9033_TUNER_IT9135_61:
	case AF9033_TUNER_IT9135_62:
		if (adap->id == 1) {
			if (state->i2c_client[3])
				af9035_del_i2c_dev(d);
		} else if (adap->id == 0) {
			if (state->i2c_client[1])
				af9035_del_i2c_dev(d);
		}
	}

	return 0;
}
