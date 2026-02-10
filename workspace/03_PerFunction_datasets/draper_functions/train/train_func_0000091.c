netxen_nic_pci_mem_access_direct(struct netxen_adapter *adapter, u64 off,
		u64 *data, int op)
{
	void __iomem *addr, *mem_ptr = NULL;
	resource_size_t mem_base;
	int ret;
	u32 start;

	spin_lock(&adapter->ahw.mem_lock);

	ret = adapter->pci_set_window(adapter, off, &start);
	if (ret != 0)
		goto unlock;

	if (NX_IS_REVISION_P3(adapter->ahw.revision_id)) {
		addr = adapter->ahw.pci_base0 + start;
	} else {
		addr = pci_base_offset(adapter, start);
		if (addr)
			goto noremap;

		mem_base = pci_resource_start(adapter->pdev, 0) +
					(start & PAGE_MASK);
		mem_ptr = ioremap(mem_base, PAGE_SIZE);
		if (mem_ptr == NULL) {
			ret = -EIO;
			goto unlock;
		}

		addr = mem_ptr + (start & (PAGE_SIZE-1));
	}
noremap:
	if (op == 0)
		*data = readq(addr);
	else
		writeq(*data, addr);

unlock:
	spin_unlock(&adapter->ahw.mem_lock);

	if (mem_ptr)
		iounmap(mem_ptr);
	return ret;
}
