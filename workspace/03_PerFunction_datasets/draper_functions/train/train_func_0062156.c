qla82xx_pci_region_offset(struct pci_dev *pdev, int region)
{
	unsigned long val = 0;
	u32 control;

	switch (region) {
	case 0:
		val = 0;
		break;
	case 1:
		pci_read_config_dword(pdev, QLA82XX_PCI_REG_MSIX_TBL, &control);
		val = control + QLA82XX_MSIX_TBL_SPACE;
		break;
	}
	return val;
}
