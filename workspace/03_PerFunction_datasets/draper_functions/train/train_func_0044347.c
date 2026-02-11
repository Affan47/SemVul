i965_write_entry(dma_addr_t addr,
			     unsigned int entry,
			     unsigned int flags)
{
	u32 pte_flags;

	pte_flags = I810_PTE_VALID;
	if (flags == AGP_USER_CACHED_MEMORY)
		pte_flags |= I830_PTE_SYSTEM_CACHED;


	addr |= (addr >> 28) & 0xf0;
	writel_relaxed(addr | pte_flags, intel_private.gtt + entry);
}
