gru_invalidate_page(struct mmu_notifier *mn, struct mm_struct *mm,
				unsigned long address)
{
	struct gru_mm_struct *gms = container_of(mn, struct gru_mm_struct,
						 ms_notifier);

	STAT(mmu_invalidate_page);
	gru_flush_tlb_range(gms, address, PAGE_SIZE);
	gru_dbg(grudev, "gms %p, address 0x%lx\n", gms, address);
}
