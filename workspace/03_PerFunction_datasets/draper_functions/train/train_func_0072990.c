xpc_get_rsvd_page_pa(int nasid)
{
	enum xp_retval ret;
	u64 cookie = 0;
	unsigned long rp_pa = nasid;
	size_t len = 0;
	size_t buf_len = 0;
	void *buf = buf;
	void *buf_base = NULL;
	enum xp_retval (*get_partition_rsvd_page_pa)
		(void *, u64 *, unsigned long *, size_t *) =
		xpc_arch_ops.get_partition_rsvd_page_pa;

	while (1) {


		ret = get_partition_rsvd_page_pa(buf, &cookie, &rp_pa, &len);

		dev_dbg(xpc_part, "SAL returned with ret=%d, cookie=0x%016lx, "
			"address=0x%016lx, len=0x%016lx\n", ret,
			(unsigned long)cookie, rp_pa, len);

		if (ret != xpNeedMoreInfo)
			break;


		if (is_shub())
			len = L1_CACHE_ALIGN(len);

		if (len > buf_len) {
			if (buf_base != NULL)
				kfree(buf_base);
			buf_len = L1_CACHE_ALIGN(len);
			buf = xpc_kmalloc_cacheline_aligned(buf_len, GFP_KERNEL,
							    &buf_base);
			if (buf_base == NULL) {
				dev_err(xpc_part, "unable to kmalloc "
					"len=0x%016lx\n", buf_len);
				ret = xpNoMemory;
				break;
			}
		}

		ret = xp_remote_memcpy(xp_pa(buf), rp_pa, len);
		if (ret != xpSuccess) {
			dev_dbg(xpc_part, "xp_remote_memcpy failed %d\n", ret);
			break;
		}
	}

	kfree(buf_base);

	if (ret != xpSuccess)
		rp_pa = 0;

	dev_dbg(xpc_part, "reserved page at phys address 0x%016lx\n", rp_pa);
	return rp_pa;
}
