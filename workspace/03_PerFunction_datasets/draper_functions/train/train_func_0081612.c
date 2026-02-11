s5h1409_set_qam_interleave_mode(struct dvb_frontend *fe)
{
	struct s5h1409_state *state = fe->demodulator_priv;
	u16 reg, reg1, reg2;

	if (state->qam_state >= QAM_STATE_INTERLEAVE_SET) {

		return;
	}

	reg = s5h1409_readreg(state, 0xf1);


	if ((reg >> 15) & 0x1) {
		if (state->qam_state == QAM_STATE_UNTUNED ||
		    state->qam_state == QAM_STATE_TUNING_STARTED) {
			dprintk("%s() setting QAM state to INTERLEAVE_SET\n",
				__func__);
			reg1 = s5h1409_readreg(state, 0xb2);
			reg2 = s5h1409_readreg(state, 0xad);

			s5h1409_writereg(state, 0x96, 0x0020);
			s5h1409_writereg(state, 0xad,
				(((reg1 & 0xf000) >> 4) | (reg2 & 0xf0ff)));
			state->qam_state = QAM_STATE_INTERLEAVE_SET;
		}
	} else {
		if (state->qam_state == QAM_STATE_UNTUNED) {
			dprintk("%s() setting QAM state to TUNING_STARTED\n",
				__func__);
			s5h1409_writereg(state, 0x96, 0x08);
			s5h1409_writereg(state, 0xab,
				s5h1409_readreg(state, 0xab) | 0x1001);
			state->qam_state = QAM_STATE_TUNING_STARTED;
		}
	}
}
