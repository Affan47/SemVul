pci_conf_read(unsigned bus, unsigned dev, unsigned fn, unsigned reg, unsigned len, unsigned long *value)
{
	int result;

	if (!value || (bus > 255) || (dev > 31) || (fn > 7) || (reg > 255 && pci_conf_type != PCI_CONF_TYPE_1))
		return -1;

	result = -1;
	switch(pci_conf_type) {
	case PCI_CONF_TYPE_1:
		if(reg < 256){
			outl(PCI_CONF1_ADDRESS(bus, dev, fn, reg), 0xCF8);
		}else{
			outl(PCI_CONF3_ADDRESS(bus, dev, fn, reg), 0xCF8);
		}
		switch(len) {
		case 1:  *value = inb(0xCFC + (reg & 3)); result = 0; break;
		case 2:  *value = inw(0xCFC + (reg & 2)); result = 0; break;
		case 4:  *value = inl(0xCFC); result = 0; break;
		}
		break;
	case PCI_CONF_TYPE_2:
		outb(0xF0 | (fn << 1), 0xCF8);
		outb(bus, 0xCFA);

		switch(len) {
		case 1:  *value = inb(PCI_CONF2_ADDRESS(dev, reg)); result = 0; break;
		case 2:  *value = inw(PCI_CONF2_ADDRESS(dev, reg)); result = 0; break;
		case 4:  *value = inl(PCI_CONF2_ADDRESS(dev, reg)); result = 0; break;
		}
		outb(0, 0xCF8);
		break;
	}
	return result;
}
