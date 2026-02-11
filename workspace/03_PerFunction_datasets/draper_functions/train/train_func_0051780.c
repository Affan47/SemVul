status_update_cands(unsigned int cands)
{
	unsigned int saved_lo = status.cands.lo;
	add32to64(&status.cands, cands);
	if ((status.cands.lo ^ saved_lo) & 0xfff00000U)
		status_ticks_overflow_safety();
}
