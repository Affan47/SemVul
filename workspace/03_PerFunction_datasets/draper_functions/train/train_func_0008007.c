sis900_get_mac_addr(struct pci_dev *pci_dev,
			       struct net_device *net_dev)
{
	struct sis900_private *sis_priv = netdev_priv(net_dev);
	void __iomem *ioaddr = sis_priv->ioaddr;
	u16 signature;
	int i;


	signature = (u16) read_eeprom(ioaddr, EEPROMSignature);
	if (signature == 0xffff || signature == 0x0000) {
		printk (KERN_WARNING "%s: Error EERPOM read %x\n",
			pci_name(pci_dev), signature);
		return 0;
	}


	for (i = 0; i < 3; i++)
	        ((u16 *)(net_dev->dev_addr))[i] = read_eeprom(ioaddr, i+EEPROMMACAddr);

	return 1;
}
