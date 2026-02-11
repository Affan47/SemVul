dib8000_set_output_mode(struct dvb_frontend *fe, int mode)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 outreg, fifo_threshold, smo_mode, sram = 0x0205;

	state->output_mode = mode;
	outreg = 0;
	fifo_threshold = 1792;
	smo_mode = (dib8000_read_word(state, 299) & 0x0050) | (1 << 1);

	dprintk("-I-	Setting output mode for demod %p to %d",
			&state->fe[0], mode);

	switch (mode) {
	case OUTMODE_MPEG2_PAR_GATED_CLK:
		outreg = (1 << 10);
		break;
	case OUTMODE_MPEG2_PAR_CONT_CLK:
		outreg = (1 << 10) | (1 << 6);
		break;
	case OUTMODE_MPEG2_SERIAL:
		outreg = (1 << 10) | (2 << 6) | (0 << 1);
		break;
	case OUTMODE_DIVERSITY:
		if (state->cfg.hostbus_diversity) {
			outreg = (1 << 10) | (4 << 6);
			sram &= 0xfdff;
		} else
			sram |= 0x0c00;
		break;
	case OUTMODE_MPEG2_FIFO:
		smo_mode |= (3 << 1);
		fifo_threshold = 512;
		outreg = (1 << 10) | (5 << 6);
		break;
	case OUTMODE_HIGH_Z:
		outreg = 0;
		break;

	case OUTMODE_ANALOG_ADC:
		outreg = (1 << 10) | (3 << 6);
		dib8000_set_acquisition_mode(state);
		break;

	default:
		dprintk("Unhandled output_mode passed to be set for demod %p",
				&state->fe[0]);
		return -EINVAL;
	}

	if (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	dib8000_write_word(state, 299, smo_mode);
	dib8000_write_word(state, 300, fifo_threshold);
	dib8000_write_word(state, 1286, outreg);
	dib8000_write_word(state, 1291, sram);

	return 0;
}
