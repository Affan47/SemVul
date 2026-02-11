m68k_natfeat_id(void)
{
	struct M68kRegisters r;
	int i;


	for (i=0; i<8; i++) {
		r.d[i] = m68k_dreg(regs, i);
		r.a[i] = m68k_areg(regs, i);
	}
	MakeSR();
	r.sr = regs.sr;

	memptr stack = r.a[7] + 4;
	r.d[0] = nf_get_id(stack);

	for (i=0; i<8; i++) {
		m68k_dreg(regs, i) = r.d[i];
		m68k_areg(regs, i) = r.a[i];
	}
	regs.sr = r.sr;
	MakeFromSR();
}
