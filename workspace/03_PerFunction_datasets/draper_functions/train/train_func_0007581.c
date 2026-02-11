int13_retry(const com32sys_t * inreg, com32sys_t * outreg)
{
    int retry = 6;
    com32sys_t tmpregs;

    if (!outreg)
	outreg = &tmpregs;

    while (retry--) {
	__intcall(0x13, inreg, outreg);
	if (!(outreg->eflags.l & EFLAGS_CF))
	    return 0;
    }

    return -1;
}
