memblock_virt_alloc_try_nid_nopanic(
				phys_addr_t size, phys_addr_t align,
				phys_addr_t min_addr, phys_addr_t max_addr,
				int nid)
{
	memblock_dbg("%s: %llu bytes align=0x%llx nid=%d from=0x%llx max_addr=0x%llx %pF\n",
		     __func__, (u64)size, (u64)align, nid, (u64)min_addr,
		     (u64)max_addr, (void *)_RET_IP_);
	return memblock_virt_alloc_internal(size, align, min_addr,
					     max_addr, nid);
}
