PowerScanInit(struct tda_state *state)
{
	int status = 0;
	do {
		state->m_Regs[EP3] = (state->m_Regs[EP3] & ~0x1F) | 0x12;
		state->m_Regs[EP4] = (state->m_Regs[EP4] & ~0x1F);
		status = UpdateRegs(state, EP3, EP4);
		if (status < 0)
			break;
		state->m_Regs[EB18] = (state->m_Regs[EB18] & ~0x03);
		status = UpdateReg(state, EB18);
		if (status < 0)
			break;
		state->m_Regs[EB21] = (state->m_Regs[EB21] & ~0x03);
		state->m_Regs[EB23] = (state->m_Regs[EB23] | 0x06);
		status = UpdateRegs(state, EB21, EB23);
		if (status < 0)
			break;
	} while (0);
	return status;
}
