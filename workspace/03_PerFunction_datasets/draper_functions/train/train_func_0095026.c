pci_check_direct(void)
{
	unsigned char tmpCFB;
	unsigned int  tmpCF8;

	if (cpu_id.vend_id[0] == 'A' && cpu_id.type == 15) {
			pci_conf_type = PCI_CONF_TYPE_1;
			return 0;
	} else {

			pci_conf_type = PCI_CONF_TYPE_1;
			tmpCFB = inb(0xCFB);
			outb(0x01, 0xCFB);
			tmpCF8 = inl(0xCF8);
			outl(0x80000000, 0xCF8);
			if ((inl(0xCF8) == 0x80000000) && (pci_sanity_check() == 0)) {
				outl(tmpCF8, 0xCF8);
				outb(tmpCFB, 0xCFB);
				return 0;
			}
			outl(tmpCF8, 0xCF8);


			pci_conf_type = PCI_CONF_TYPE_2;
			outb(0x00, 0xCFB);
			outb(0x00, 0xCF8);
			outb(0x00, 0xCFA);
			if (inb(0xCF8) == 0x00 && inb(0xCFA) == 0x00 && (pci_sanity_check() == 0)) {
				outb(tmpCFB, 0xCFB);
				return 0;
	}

	outb(tmpCFB, 0xCFB);


	pci_conf_type = PCI_CONF_TYPE_NONE;
	return -1;

	}
}
