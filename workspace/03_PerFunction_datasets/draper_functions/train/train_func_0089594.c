stb0899_search_data(struct stb0899_state *state)
{
	short int derot_freq, derot_step, derot_limit, next_loop = 3;
	u8 cfr[2];
	u8 reg;
	int index = 1;

	struct stb0899_internal *internal = &state->internal;
	struct stb0899_params *params = &state->params;

	derot_step = (params->srate / 4L) / internal->mclk;
	derot_limit = (internal->sub_range / 2L) / internal->mclk;
	derot_freq = internal->derot_freq;

	do {
		if ((internal->status != CARRIEROK) || (stb0899_check_data(state) != DATAOK)) {

			derot_freq += index * internal->direction * derot_step;
			if (abs(derot_freq) > derot_limit)
				next_loop--;

			if (next_loop) {
				dprintk(state->verbose, FE_DEBUG, 1, "Derot freq=%d, mclk=%d", derot_freq, internal->mclk);
				reg = stb0899_read_reg(state, STB0899_CFD);
				STB0899_SETFIELD_VAL(CFD_ON, reg, 1);
				stb0899_write_reg(state, STB0899_CFD, reg);

				STB0899_SETFIELD_VAL(CFRM, cfr[0], MSB(internal->inversion * derot_freq));
				STB0899_SETFIELD_VAL(CFRL, cfr[1], LSB(internal->inversion * derot_freq));
				stb0899_write_regs(state, STB0899_CFRM, cfr, 2);

				stb0899_check_carrier(state);
				index++;
			}
		}
		internal->direction = -internal->direction;
	} while ((internal->status != DATAOK) && next_loop);

	if (internal->status == DATAOK) {
		stb0899_read_regs(state, STB0899_CFRM, cfr, 2);


		reg = stb0899_read_reg(state, STB0899_IQSWAP);
		if (STB0899_GETFIELD(SYM, reg))
			internal->inversion = IQ_SWAP_ON;
		else
			internal->inversion = IQ_SWAP_OFF;

		internal->derot_freq = internal->inversion * MAKEWORD16(cfr[0], cfr[1]);
		dprintk(state->verbose, FE_DEBUG, 1, "------> DATAOK ! Derot Freq=%d", internal->derot_freq);
	}

	return internal->status;
}
