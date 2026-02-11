sis96x_get_mac_addr(struct pci_dev *pci_dev,
			       struct net_device *net_dev)
{
	struct sis900_private *sis_priv = netdev_priv(net_dev);
	void __iomem *ioaddr = sis_priv->ioaddr;
	int wait, rc = 0;

	sw32(mear, EEREQ);
	for (wait = 0; wait < 2000; wait++) {
		if (sr32(mear) & EEGNT) {
			u16 *mac = (u16 *)net_dev->dev_addr;
			int i;


			for (i = 0; i < 3; i++)
			        mac[i] = read_eeprom(ioaddr, i + EEPROMMACAddr);

			rc = 1;
			break;
		}
		udelay(1);
	}
	sw32(mear, EEDONE);
	return rc;
}
