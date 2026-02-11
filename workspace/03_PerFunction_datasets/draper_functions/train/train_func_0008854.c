default_xlate (uaecptr a)
{
	if (quit_program == 0) {

		if ((currprefs.cpu_model > 68000 || !currprefs.cpu_compatible) && !currprefs.mmu_model) {
#if defined(ENFORCER)
			enforcer_disable ();
#endif

			if (be_cnt < 3) {
				int i, j;
				uaecptr a2 = a - 32;
				uaecptr a3 = m68k_getpc () - 32;
				write_log (_T("Your Amiga program just did something terribly stupid %08X PC=%08X\n"), a, M68K_GETPC);
				if (debugging || DEBUG_STUPID)
					activate_debugger ();
				m68k_dumpstate (0, 0);
				for (i = 0; i < 10; i++) {
					write_log (_T("%08X "), i >= 5 ? a3 : a2);
					for (j = 0; j < 16; j += 2) {
						write_log (_T(" %04X"), get_word (i >= 5 ? a3 : a2));
						if (i >= 5) a3 += 2; else a2 += 2;
					}
					write_log (_T("\n"));
				}
				memory_map_dump ();
			}
			be_cnt++;
			if (be_cnt > 1000) {
				uae_reset (0, 0);
				be_cnt = 0;
			} else {
				regs.panic = 1;
				regs.panic_pc = m68k_getpc ();
				regs.panic_addr = a;
				set_special (SPCFLAG_BRK);
			}
		}
	}
	return kickmem_xlate (2);
}
