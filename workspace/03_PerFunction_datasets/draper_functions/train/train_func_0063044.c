pmem_rw_bytes(struct nd_namespace_common *ndns,
		resource_size_t offset, void *buf, size_t size, int rw)
{
	struct pmem_device *pmem = dev_get_drvdata(ndns->claim);

	if (unlikely(offset + size > pmem->size)) {
		dev_WARN_ONCE(&ndns->dev, 1, "request out of range\n");
		return -EFAULT;
	}

	if (rw == READ)
		memcpy_from_pmem(buf, pmem->virt_addr + offset, size);
	else {
		memcpy_to_pmem(pmem->virt_addr + offset, buf, size);
		wmb_pmem();
	}

	return 0;
}
