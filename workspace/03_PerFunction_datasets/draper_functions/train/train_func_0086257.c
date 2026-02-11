memblock_virt_alloc_try_nid(
			phys_addr_t size, phys_addr_t align,
			phys_addr_t min_addr, phys_addr_t max_addr,
			int nid)
{
	void *ptr;

	memblock_dbg("%s: %llu bytes align=0x%llx nid=%d from=0x%llx max_addr=0x%llx %pF\n",
		     __func__, (u64)size, (u64)align, nid, (u64)min_addr,
		     (u64)max_addr, (void *)_RET_IP_);
	ptr = memblock_virt_alloc_internal(size, align,
					   min_addr, max_addr, nid);
	if (ptr)
		return ptr;

	panic("%s: Failed to allocate %llu bytes align=0x%llx nid=%d from=0x%llx max_addr=0x%llx\n",
	      __func__, (u64)size, (u64)align, nid, (u64)min_addr,
	      (u64)max_addr);
	return NULL;
}
