be_cmd_page_addrs_prepare(struct phys_addr *pages, u32 max_pages,
							struct be_dma_mem *mem)
{
	int i, buf_pages;
	u64 dma = (u64) mem->dma;

	buf_pages = min(PAGES_4K_SPANNED(mem->va, mem->size), max_pages);
	for (i = 0; i < buf_pages; i++) {
		pages[i].lo = cpu_to_le32(dma & 0xFFFFFFFF);
		pages[i].hi = cpu_to_le32(upper_32_bits(dma));
		dma += PAGE_SIZE_4K;
	}
}
