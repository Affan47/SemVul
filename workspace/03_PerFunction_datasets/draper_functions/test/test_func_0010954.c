cia_bget (uaecptr addr)
{
	int r = (addr & 0xf00) >> 8;
	uae_u8 v = 0xff;

#ifdef JIT
	special_mem |= S_READ;
#endif

	if (!isgaylenocia (addr))
		return v;

	cia_wait_pre ();
	switch ((addr >> 12) & 3) {
	case 0:
		if (!issinglecia ())
			v = (addr & 1) ? ReadCIAA (r) : ReadCIAB (r);
		break;
	case 1:
		v = (addr & 1) ? 0xff : ReadCIAB (r);
		break;
	case 2:
		v = (addr & 1) ? ReadCIAA (r) : 0xff;
		break;
	case 3:
		if (currprefs.cpu_model == 68000 && currprefs.cpu_compatible)
			v = (addr & 1) ? regs.irc : regs.irc >> 8;
		if (warned > 0) {
			write_log (_T("cia_bget: unknown CIA address %x PC=%x\n"), addr, M68K_GETPC);
			warned--;
		}
		break;
	}
	cia_wait_post (v);

	return v;
}
