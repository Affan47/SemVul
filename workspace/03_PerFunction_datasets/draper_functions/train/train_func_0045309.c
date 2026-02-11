reset_sar(struct atm_dev *dev)
{
	IADEV *iadev;
	int i, error = 1;
	unsigned int pci[64];

	iadev = INPH_IA_DEV(dev);
	for(i=0; i<64; i++)
	  if ((error = pci_read_config_dword(iadev->pci,
				i*4, &pci[i])) != PCIBIOS_SUCCESSFUL)
  	      return error;
	writel(0, iadev->reg+IPHASE5575_EXT_RESET);
	for(i=0; i<64; i++)
	  if ((error = pci_write_config_dword(iadev->pci,
					i*4, pci[i])) != PCIBIOS_SUCCESSFUL)
	    return error;
	udelay(5);
	return 0;
}
