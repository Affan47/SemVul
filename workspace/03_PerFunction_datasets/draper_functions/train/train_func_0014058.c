tda8261_get_status(struct dvb_frontend *fe, u32 *status)
{
	struct tda8261_state *state = fe->tuner_priv;
	u8 result = 0;
	int err = 0;

	*status = 0;

	if ((err = tda8261_read(state, &result)) < 0) {
		pr_err("%s: I/O Error\n", __func__);
		return err;
	}
	if ((result >> 6) & 0x01) {
		pr_debug("%s: Tuner Phase Locked\n", __func__);
		*status = 1;
	}

	return err;
}
