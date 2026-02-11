m68k_run_1 (void)
{
	struct regstruct *r = &regs;

	for (;;) {
		uae_u16 opcode = r->ir;

		count_instr (opcode);

#if DEBUG_CD32CDTVIO
		out_cd32io (m68k_getpc ());
#endif

#if 0
		int pc = m68k_getpc ();
		if (pc == 0xdff002)
			write_log (_T("hip\n"));
		if (pc != pcs[0] && (pc < 0xd00000 || pc > 0x1000000)) {
			memmove (pcs + 1, pcs, 998 * 4);
			pcs[0] = pc;

		}
#endif
		do_cycles (cpu_cycles);
		cpu_cycles = (*cpufunctbl[opcode])(opcode);
		cpu_cycles = adjust_cycles (cpu_cycles);
		if (r->spcflags) {
			if (do_specialties (cpu_cycles)) {
				regs.ipl = regs.ipl_pin;
				return;
			}
		}
		regs.ipl = regs.ipl_pin;
		if (!currprefs.cpu_compatible || (currprefs.cpu_cycle_exact && currprefs.cpu_model <= 68000))
			return;
	}
}
