set_tv_freq(struct i2c_client *c, unsigned int freq)
{
	struct tuner *t = to_tuner(i2c_get_clientdata(c));
	struct analog_demod_ops *analog_ops = &t->fe.ops.analog_ops;

	struct analog_parameters params = {
		.mode      = t->mode,
		.audmode   = t->audmode,
		.std       = t->std
	};

	if (t->type == UNSET) {
		tuner_warn("tuner type not set\n");
		return;
	}
	if (NULL == analog_ops->set_params) {
		tuner_warn("Tuner has no way to set tv freq\n");
		return;
	}
	if (freq < tv_range[0] * 16 || freq > tv_range[1] * 16) {
		tuner_dbg("TV freq (%d.%02d) out of range (%d-%d)\n",
			   freq / 16, freq % 16 * 100 / 16, tv_range[0],
			   tv_range[1]);


		if (freq < tv_range[0] * 16)
			freq = tv_range[0] * 16;
		else
			freq = tv_range[1] * 16;
	}
	params.frequency = freq;
	tuner_dbg("tv freq set to %d.%02d\n",
			freq / 16, freq % 16 * 100 / 16);
	t->tv_freq = freq;
	t->standby = false;

	analog_ops->set_params(&t->fe, &params);
}
