predictor_zero(struct g726_state *state_ptr)
{
	int		i;
	int		sezi;
	for (sezi = 0, i = 0; i < 6; i++)
		sezi += fmult(state_ptr->b[i] >> 2, state_ptr->dq[i]);
	return sezi;
}
