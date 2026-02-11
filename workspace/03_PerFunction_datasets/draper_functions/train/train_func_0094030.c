nvidia_save_vga(struct nvidia_par *par,
			    struct _riva_hw_state *state)
{
	int i;

	NVTRACE_ENTER();
	NVLockUnlock(par, 0);

	NVUnloadStateExt(par, state);

	state->misc_output = NVReadMiscOut(par);

	for (i = 0; i < NUM_CRT_REGS; i++)
		state->crtc[i] = NVReadCrtc(par, i);

	for (i = 0; i < NUM_ATC_REGS; i++)
		state->attr[i] = NVReadAttr(par, i);

	for (i = 0; i < NUM_GRC_REGS; i++)
		state->gra[i] = NVReadGr(par, i);

	for (i = 0; i < NUM_SEQ_REGS; i++)
		state->seq[i] = NVReadSeq(par, i);
	NVTRACE_LEAVE();
}
