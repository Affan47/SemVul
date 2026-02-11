dib7090_set_diversity_in(struct dvb_frontend *fe, int onoff)
{
	struct dib7000p_state *state = fe->demodulator_priv;
	u16 reg_1287;

	switch (onoff) {
	case 0:
			dprintk("%s mode OFF : by default Enable Mpeg INPUT", __func__);
			dib7090_cfg_DibRx(state, 8, 5, 0, 0, 0, 8, 0);


			reg_1287 = dib7000p_read_word(state, 1287);

			if ((reg_1287 & 0x1) == 1) {

				reg_1287 &= ~0x1;
				dib7000p_write_word(state, 1287, reg_1287);
			}
			state->input_mode_mpeg = 1;
			break;
	case 1:
	case 2:
			dprintk("%s ON : Enable diversity INPUT", __func__);
			dib7090_cfg_DibRx(state, 5, 5, 0, 0, 0, 0, 0);
			state->input_mode_mpeg = 0;
			break;
	}

	dib7000p_set_diversity_in(&state->demod, onoff);
	return 0;
}
