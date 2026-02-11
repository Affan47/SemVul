get_e801(void)
{
    int err;
    com32sys_t regs;

    memset(&regs, 0, sizeof regs);

    regs.eax.w[0] = 0xe801;
    intcall(0x15, &regs, &regs);

    if (!(err = regs.eflags.l & 1)) {
	if (regs.eax.w[0]) {
	    insertrange(0x100000, (uint64_t) ((uint32_t) regs.eax.w[0] << 10),
			1);
	}
	if (regs.ebx.w[0]) {
	    insertrange(0x1000000, (uint64_t) ((uint32_t) regs.ebx.w[0] << 16),
			1);
	}

	printf("e801: %04x %04x\n", regs.eax.w[0], regs.ebx.w[0]);
    }

    return err;
}
