ccdbg_state_replace_xmem(struct ccdbg *dbg, struct ccstate *state,
			 uint16_t addr, uint8_t *bytes, int nbytes)
{
	int i;
	if (state->mask & CC_STATE_ACC)
		ccdbg_state_replace(ACC(0), state->acc, "acc",
				    addr, bytes, nbytes);
	for (i = 0; i < CC_STATE_NSFR; i++)
		if (state->mask & sfrs[i].mask)
			ccdbg_state_replace(sfrs[i].address, state->sfr[i],
					    sfrs[i].name, addr, bytes, nbytes);
}
