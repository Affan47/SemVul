bsdsocklib_Close (TrapContext *context)
{
	int opencount;

	uae_u32 base = m68k_areg (regs, 6);
	uae_u32 negsize = get_word (base + 16);

	free_socketbase (context);

	put_word (SockLibBase + 32, opencount = get_word (SockLibBase + 32) - 1);

	m68k_areg (regs, 1) = base - negsize;
	m68k_dreg (regs, 0) = negsize + get_word (base + 18);
	CallLib (context, get_long (4), -0xD2);

	BSDTRACE ((_T("CloseLibrary() -> [%d]\n"), opencount));

	return 0;
}
