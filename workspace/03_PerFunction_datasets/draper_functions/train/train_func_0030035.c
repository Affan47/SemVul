mmu_set_tc(uae_u16 tc)
{
	if (regs.tc == tc)
		return;

	regs.tc = tc;
	regs.mmu_enabled = tc & 0x8000 ? 1 : 0;
	regs.mmu_pagesize_8k = tc & 0x4000 ? 1 : 0;
	mmu_flush_atc_all(true);

	D(bug("MMU: enabled=%d page8k=%d\n", regs.mmu_enabled, regs.mmu_pagesize_8k));
}
