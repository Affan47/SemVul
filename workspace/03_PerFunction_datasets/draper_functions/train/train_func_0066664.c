MXL_SynthIFLO_Calc(struct dvb_frontend *fe)
{
	struct mxl5005s_state *state = fe->tuner_priv;
	if (state->Mode == 1)
		state->IF_LO = state->IF_OUT;
	else  {
		if (state->IF_Mode == 0)
			state->IF_LO = state->IF_OUT + 400000;
		else
			state->IF_LO = state->IF_OUT + state->Chan_Bandwidth/2;
	}
}
