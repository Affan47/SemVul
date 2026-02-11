fpuop_dbcc (uae_u32 opcode, uae_u16 extra)
{
	uaecptr pc = (uae_u32) m68k_getpc ();
	uae_s32 disp;
	int cc;

#if DEBUG_FPP
	if (!isinrom ())
		write_log (_T("fdbcc_opp at %08lx\n"), m68k_getpc ());
#endif
	if (fault_if_no_fpu (opcode, 4))
		return;

	regs.fpiar = m68k_getpc () - 4;
	disp = (uae_s32) (uae_s16) x_next_iword ();
	cc = fpp_cond (extra & 0x3f);
	if (cc == -1) {
		fpu_op_illg (opcode, 4);
	} else if (!cc) {
		int reg = opcode & 0x7;

		m68k_dreg (regs, reg) = ((m68k_dreg (regs, reg) & 0xffff0000)
			| (((m68k_dreg (regs, reg) & 0xffff) - 1) & 0xffff));
		if ((m68k_dreg (regs, reg) & 0xffff) != 0xffff)
			m68k_setpc (pc + disp);
	}
}
