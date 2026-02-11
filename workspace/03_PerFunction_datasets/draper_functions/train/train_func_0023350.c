vmm_munmap(void *addr, size_t length)
{
#if defined(HAS_MMAP)
	int ret;

	assert_vmm_is_allocated(addr, length, VMF_MAPPED);

	ret = munmap(addr, length);

	if G_LIKELY(0 == ret) {
		pmap_remove(vmm_pmap(), addr, round_pagesize_fast(length));
		vmm_stats.munmaps++;

		if (vmm_debugging(5)) {
			s_debug("VMM unmapped %zuKiB region at %p", length / 1024, addr);
		}
	} else {
		s_warning("munmap() failed: %m");
	}

	return ret;
#else
	(void) addr;
	(void) length;
	g_assert_not_reached();

	return -1;
#endif
}
