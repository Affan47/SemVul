netxen_nic_hw_read_wx_128M(struct netxen_adapter *adapter, ulong off)
{
	unsigned long flags;
	void __iomem *addr, *mem_ptr = NULL;
	u32 data;

	addr = netxen_nic_map_indirect_address_128M(adapter, off, &mem_ptr);
	if (!addr)
		return -EIO;

	if (ADDR_IN_WINDOW1(off)) {
		data = netxen_nic_io_read_128M(adapter, addr);
	} else {
		write_lock_irqsave(&adapter->ahw.crb_lock, flags);
		netxen_nic_pci_set_crbwindow_128M(adapter, 0);
		data = readl(addr);
		netxen_nic_pci_set_crbwindow_128M(adapter,
				NETXEN_WINDOW_ONE);
		write_unlock_irqrestore(&adapter->ahw.crb_lock, flags);
	}

	if (mem_ptr)
		iounmap(mem_ptr);

	return data;
}
