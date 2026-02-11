rv370_pcie_gart_get_page_entry(uint64_t addr, uint32_t flags)
{
	addr = (lower_32_bits(addr) >> 8) |
		((upper_32_bits(addr) & 0xff) << 24);
	if (flags & RADEON_GART_PAGE_READ)
		addr |= R300_PTE_READABLE;
	if (flags & RADEON_GART_PAGE_WRITE)
		addr |= R300_PTE_WRITEABLE;
	if (!(flags & RADEON_GART_PAGE_SNOOP))
		addr |= R300_PTE_UNSNOOPED;
	return addr;
}
