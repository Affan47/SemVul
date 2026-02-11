lgdt3303_read_snr(struct dvb_frontend* fe, u16* snr)
{
	struct lgdt330x_state* state = (struct lgdt330x_state*) fe->demodulator_priv;
	u8 buf[5];
	u32 noise;
	u32 c;

	switch(state->current_modulation) {
	case VSB_8:
		i2c_read_demod_bytes(state, LGDT3303_EQPH_ERR0, buf, 5);
#ifdef USE_EQMSE


		noise = ((buf[0] & 0x78) << 13) | (buf[1] << 8) | buf[2];
		c = 73957994;
#else


		noise = ((buf[0] & 7) << 16) | (buf[3] << 8) | buf[4];
		c = 73957994;
#endif
		break;
	case QAM_64:
	case QAM_256:
		i2c_read_demod_bytes(state, CARRIER_MSEQAM1, buf, 2);
		noise = (buf[0] << 8) | buf[1];
		c = state->current_modulation == QAM_64 ? 97939837 : 98026066;

		break;
	default:
		printk(KERN_ERR "lgdt330x: %s: Modulation set to unsupported value\n",
		       __func__);
		return -EREMOTEIO;
	}

	state->snr = calculate_snr(noise, c);
	*snr = (state->snr) >> 16;

	dprintk("%s: noise = 0x%08x, snr = %d.%02d dB\n", __func__, noise,
		state->snr >> 24, (((state->snr >> 8) & 0xffff) * 100) >> 16);

	return 0;
}
