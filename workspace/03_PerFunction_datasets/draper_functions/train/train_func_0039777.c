avm_pci_setup(struct IsdnCardState *cs)
{
	if ((dev_avm = hisax_find_pci_device(PCI_VENDOR_ID_AVM,
					     PCI_DEVICE_ID_AVM_A1, dev_avm))) {

		if (pci_enable_device(dev_avm))
			return (0);

		cs->irq = dev_avm->irq;
		if (!cs->irq) {
			printk(KERN_ERR "FritzPCI: No IRQ for PCI card found\n");
			return (0);
		}

		cs->hw.avm.cfg_reg = pci_resource_start(dev_avm, 1);
		if (!cs->hw.avm.cfg_reg) {
			printk(KERN_ERR "FritzPCI: No IO-Adr for PCI card found\n");
			return (0);
		}

		cs->subtyp = AVM_FRITZ_PCI;
	} else {
		printk(KERN_WARNING "FritzPCI: No PCI card found\n");
		return (0);
	}

	cs->irq_flags |= IRQF_SHARED;

	return (1);
}
