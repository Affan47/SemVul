netxen_nic_hw_read_wx_2M(struct netxen_adapter *adapter, ulong off)
{
	unsigned long flags;
	int rv;
	u32 data;
	void __iomem *addr = NULL;

	rv = netxen_nic_pci_get_crb_addr_2M(adapter, off, &addr);

	if (rv == 0)
		return readl(addr);

	if (rv > 0) {

		write_lock_irqsave(&adapter->ahw.crb_lock, flags);
		crb_win_lock(adapter);
		netxen_nic_pci_set_crbwindow_2M(adapter, off);
		data = readl(addr);
		crb_win_unlock(adapter);
		write_unlock_irqrestore(&adapter->ahw.crb_lock, flags);
		return data;
	}

	dev_err(&adapter->pdev->dev,
			"%s: invalid offset: 0x%016lx\n", __func__, off);
	dump_stack();
	return -1;
}
