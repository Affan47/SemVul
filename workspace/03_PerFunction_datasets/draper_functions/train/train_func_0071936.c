gp8psk_fe_set_tone(struct dvb_frontend *fe,
			      enum fe_sec_tone_mode tone)
{
	struct gp8psk_fe_state* state = fe->demodulator_priv;

	if (gp8psk_usb_out_op(state->d,SET_22KHZ_TONE,
		 (tone == SEC_TONE_ON), 0, NULL, 0)) {
		return -EINVAL;
	}
	return 0;
}
