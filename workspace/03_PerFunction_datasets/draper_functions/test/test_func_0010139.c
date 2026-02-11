fmv_wget (uaecptr addr)
{
	uae_u32 v;
	addr -= fmv_start & fmv_mask;
	addr &= fmv_mask;
	int mask = addr & BANK_MASK;
	if (mask == L64111_BASE)
		v = l64111_wget (addr);
	else if (mask == CL450_BASE)
		v = cl450_wget (addr);
	else if (mask == IO_BASE)
		v = io_wget (addr);
	else
		v = romram_wget (addr);

#ifdef FMV_DEBUG
	if (isdebug (addr))
		write_log (_T("fmv_wget %08X=%04X PC=%08X\n"), addr, v, M68K_GETPC);
#endif
	return v;
}
