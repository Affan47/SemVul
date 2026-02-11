cciss_find_cfg_addrs(struct pci_dev *pdev, void __iomem *vaddr,
				u32 *cfg_base_addr, u64 *cfg_base_addr_index,
				u64 *cfg_offset)
{
	*cfg_base_addr = readl(vaddr + SA5_CTCFG_OFFSET);
	*cfg_offset = readl(vaddr + SA5_CTMEM_OFFSET);
	*cfg_base_addr &= (u32) 0x0000ffff;
	*cfg_base_addr_index = find_PCI_BAR_index(pdev, *cfg_base_addr);
	if (*cfg_base_addr_index == -1) {
		dev_warn(&pdev->dev, "cannot find cfg_base_addr_index, "
			"*cfg_base_addr = 0x%08x\n", *cfg_base_addr);
		return -ENODEV;
	}
	return 0;
}
