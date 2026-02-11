stv090x_get_viterbi(struct stv090x_state *state)
{
	u32 reg, rate;

	reg = STV090x_READ_DEMOD(state, VITCURPUN);
	rate = STV090x_GETFIELD_Px(reg, VIT_CURPUN_FIELD);

	switch (rate) {
	case 13:
		state->fec = STV090x_PR12;
		break;

	case 18:
		state->fec = STV090x_PR23;
		break;

	case 21:
		state->fec = STV090x_PR34;
		break;

	case 24:
		state->fec = STV090x_PR56;
		break;

	case 25:
		state->fec = STV090x_PR67;
		break;

	case 26:
		state->fec = STV090x_PR78;
		break;

	default:
		state->fec = STV090x_PRERR;
		break;
	}

	return 0;
}
