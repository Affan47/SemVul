mt2050_set_radio_freq(struct dvb_frontend *fe,
				 struct analog_parameters *params)
{
	struct microtune_priv *priv = fe->tuner_priv;
	int if2;

	if (params->std & V4L2_STD_525_60) {
		tuner_dbg("pinnacle ntsc\n");
		if2 = 41300 * 1000;
	} else {
		tuner_dbg("pinnacle pal\n");
		if2 = 33300 * 1000;
	}

	mt2050_set_if_freq(fe, params->frequency * 125 / 2, if2);
	mt2050_set_antenna(fe, radio_antenna);

	return 0;
}
