fmv_wput (uaecptr addr, uae_u32 w)
{
	addr -= fmv_start & fmv_mask;
	addr &= fmv_mask;
#ifdef FMV_DEBUG
	if (isdebug (addr))
		write_log (_T("fmv_wput %04X=%04X PC=%08X\n"), addr, w & 65535, M68K_GETPC);
#endif
	int mask = addr & BANK_MASK;
	if (mask == L64111_BASE)
		l64111_wput (addr, w);
	else if (mask == CL450_BASE)
		cl450_wput (addr, w);
	else if (mask == IO_BASE)
		io_wput (addr, w);
	else
		ram_wput (addr, w);
}
