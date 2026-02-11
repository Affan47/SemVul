ncr_lput (uaecptr addr, uae_u32 l)
{
#ifdef JIT
	special_mem |= S_WRITE;
#endif
	addr &= board_mask;
#if NCR_DEBUG > 0
	if (addr < ROM_VECTOR)
		write_log (_T("ncr_lput %08X=%08X PC=%08X\n"), addr, l, M68K_GETPC);
#endif
	ncr_bput2 (addr, l >> 24);
	ncr_bput2 (addr + 1, l >> 16);
	ncr_bput2 (addr + 2, l >> 8);
	ncr_bput2 (addr + 3, l);
}
