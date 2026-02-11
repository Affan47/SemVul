ts2020_get_tuner_gain(struct dvb_frontend *fe, __s64 *_gain)
{
	struct ts2020_priv *priv = fe->tuner_priv;
	int v_agc = 0, ret;
	u8 agc_pwm;


	if (priv->get_agc_pwm) {
		ret = priv->get_agc_pwm(fe, &agc_pwm);
		if (ret < 0)
			return ret;

		switch (priv->tuner) {
		case TS2020_M88TS2020:
			v_agc = (int)agc_pwm * 20 - 1166;
			break;
		case TS2020_M88TS2022:
			v_agc = (int)agc_pwm * 16 - 670;
			break;
		}

		if (v_agc < 0)
			v_agc = 0;
	}

	return ts2020_read_tuner_gain(fe, v_agc, _gain);
}
