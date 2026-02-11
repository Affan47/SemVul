eprom_set(struct zatm_dev *zatm_dev, unsigned long value,
		      unsigned short cmd)
{
	int error;

	if ((error = pci_write_config_dword(zatm_dev->pci_dev,cmd,value)))
		printk(KERN_ERR DEV_LABEL ": PCI write failed (0x%02x)\n",
		    error);
}
