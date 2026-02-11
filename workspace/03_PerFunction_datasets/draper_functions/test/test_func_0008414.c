s5h1420_get_status_bits(struct s5h1420_state *state)
{
	u8 val;
	enum fe_status status = 0;

	val = s5h1420_readreg(state, 0x14);
	if (val & 0x02)
		status |=  FE_HAS_SIGNAL;
	if (val & 0x01)
		status |=  FE_HAS_CARRIER;
	val = s5h1420_readreg(state, 0x36);
	if (val & 0x01)
		status |=  FE_HAS_VITERBI;
	if (val & 0x20)
		status |=  FE_HAS_SYNC;
	if (status == (FE_HAS_SIGNAL|FE_HAS_CARRIER|FE_HAS_VITERBI|FE_HAS_SYNC))
		status |=  FE_HAS_LOCK;

	return status;
}
