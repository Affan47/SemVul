atp867x_fixup(struct ata_host *host)
{
	struct pci_dev *pdev = to_pci_dev(host->dev);
	struct ata_port *ap = host->ports[0];
	int i;
	u8 v;


	pci_read_config_byte(pdev, PCI_LATENCY_TIMER, &v);
	if (v < 0x80) {
		v = 0x80;
		pci_write_config_byte(pdev, PCI_LATENCY_TIMER, v);
		printk(KERN_DEBUG "ATP867X: set latency timer of device %s"
			" to %d\n", pci_name(pdev), v);
	}


	for (i = 0; i < ATP867X_NUM_PORTS; i++)
		iowrite16(ATP867X_IO_PORTSPD_VAL, ATP867X_IO_PORTSPD(ap, i));


	for (i = 0; i < ATP867X_NUM_PORTS; i++)
		iowrite16(ATP867X_PREREAD_VAL, ATP867X_IO_PREREAD(ap, i));

	v = ioread8(ATP867X_IOBASE(ap) + 0x28);
	v &= 0xcf;
	v |= 0xc0;
	iowrite8(v, ATP867X_IOBASE(ap) + 0x28);


	v = ioread8(ATP867X_SYS_INFO(ap));
	v &= ATP867X_IO_SYS_MASK_RESERVED;
	if (pdev->device == PCI_DEVICE_ID_ARTOP_ATP867B)
		v |= ATP867X_IO_SYS_INFO_SLOW_UDMA5;
	iowrite8(v, ATP867X_SYS_INFO(ap));
}
