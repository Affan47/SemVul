quirk_via_vlink(struct pci_dev *dev)
{
	u8 irq, new_irq;


	if (via_vlink_dev_lo == -1)
		return;

	new_irq = dev->irq;


	if (!new_irq || new_irq > 15)
		return;


	if (dev->bus->number != 0 || PCI_SLOT(dev->devfn) > via_vlink_dev_hi ||
	    PCI_SLOT(dev->devfn) < via_vlink_dev_lo)
		return;


	pci_read_config_byte(dev, PCI_INTERRUPT_LINE, &irq);
	if (new_irq != irq) {
		dev_info(&dev->dev, "VIA VLink IRQ fixup, from %d to %d\n",
			irq, new_irq);
		udelay(15);
		pci_write_config_byte(dev, PCI_INTERRUPT_LINE, new_irq);
	}
}
