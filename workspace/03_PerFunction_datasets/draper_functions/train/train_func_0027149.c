nvidia_write_regs(struct nvidia_par *par,
			      struct _riva_hw_state *state)
{
	int i;

	NVTRACE_ENTER();

	NVLoadStateExt(par, state);

	NVWriteMiscOut(par, state->misc_output);

	for (i = 1; i < NUM_SEQ_REGS; i++) {
#ifdef DUMP_REG
		printk(" SEQ[%02x] = %08x\n", i, state->seq[i]);
#endif
		NVWriteSeq(par, i, state->seq[i]);
	}


	NVWriteCrtc(par, 0x11, state->crtc[0x11] & ~0x80);

	for (i = 0; i < NUM_CRT_REGS; i++) {
		switch (i) {
		case 0x19:
		case 0x20 ... 0x40:
			break;
		default:
#ifdef DUMP_REG
			printk("CRTC[%02x] = %08x\n", i, state->crtc[i]);
#endif
			NVWriteCrtc(par, i, state->crtc[i]);
		}
	}

	for (i = 0; i < NUM_GRC_REGS; i++) {
#ifdef DUMP_REG
		printk(" GRA[%02x] = %08x\n", i, state->gra[i]);
#endif
		NVWriteGr(par, i, state->gra[i]);
	}

	for (i = 0; i < NUM_ATC_REGS; i++) {
#ifdef DUMP_REG
		printk("ATTR[%02x] = %08x\n", i, state->attr[i]);
#endif
		NVWriteAttr(par, i, state->attr[i]);
	}

	NVTRACE_LEAVE();
}
