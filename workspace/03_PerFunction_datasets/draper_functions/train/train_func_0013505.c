af9013_statistics_signal_strength(struct dvb_frontend *fe)
{
	struct af9013_state *state = fe->demodulator_priv;
	int ret = 0;
	u8 buf[2], rf_gain, if_gain;
	int signal_strength;

	dev_dbg(&state->i2c->dev, "%s:\n", __func__);

	if (!state->signal_strength_en)
		return 0;

	ret = af9013_rd_regs(state, 0xd07c, buf, 2);
	if (ret)
		goto err;

	rf_gain = buf[0];
	if_gain = buf[1];

	signal_strength = (0xffff / \
		(9 * (state->rf_50 + state->if_50) - \
		11 * (state->rf_80 + state->if_80))) * \
		(10 * (rf_gain + if_gain) - \
		11 * (state->rf_80 + state->if_80));
	if (signal_strength < 0)
		signal_strength = 0;
	else if (signal_strength > 0xffff)
		signal_strength = 0xffff;

	state->signal_strength = signal_strength;

	return ret;
err:
	dev_dbg(&state->i2c->dev, "%s: failed=%d\n", __func__, ret);
	return ret;
}
