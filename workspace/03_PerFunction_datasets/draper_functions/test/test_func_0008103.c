inprec_playdebug (uae_u32 val)
{
#if INPUTRECORD_DEBUG > 0
	extern void activate_debugger (void);
	static uae_u32 pcs[16];
	int err = 0;
	if (inprec_pstart (INPREC_DEBUG)) {
		uae_u32 seed1 = uaerandgetseed ();
		uae_u32 seed2 = inprec_pu32 ();
		if (seed1 != seed2) {
			write_log (_T("SYNC ERROR seed %08x != %08x\n"), seed1, seed2);
			err = 1;
		}
		uae_u32 val2 = inprec_pu32 ();
		if (val != val2) {
			write_log (_T("SYNC ERROR val %08x != %08x\n"), val, val2);
			err = 1;
		}
		inprec_pend ();
	} else if (input_play > 0) {
		gui_message (_T("SYNC ERROR debug event missing!?\n"));
	}
#endif
}
