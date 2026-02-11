lio_pci_writeq(struct octeon_device *oct,
		    u64 val,
		    u64 addr)
{
	u32 val32;
	unsigned long flags;

	spin_lock_irqsave(&oct->pci_win_lock, flags);

	writeq(addr, oct->reg_list.pci_win_wr_addr);


	writel(val >> 32, oct->reg_list.pci_win_wr_data_hi);

	val32 = readl(oct->reg_list.pci_win_wr_data_hi);

	writel(val & 0xffffffff, oct->reg_list.pci_win_wr_data_lo);

	spin_unlock_irqrestore(&oct->pci_win_lock, flags);
}
