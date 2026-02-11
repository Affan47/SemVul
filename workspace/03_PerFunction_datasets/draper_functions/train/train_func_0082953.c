quirk_via_cx700_pci_parking_caching(struct pci_dev *dev)
{


	struct pci_dev *p = pci_get_device(PCI_VENDOR_ID_VIA,
		PCI_DEVICE_ID_VIA_8235_USB_2, NULL);
	uint8_t b;


	p = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8235_USB_2, p);
	if (!p)
		return;
	pci_dev_put(p);

	if (pci_read_config_byte(dev, 0x76, &b) == 0) {
		if (b & 0x40) {

			pci_write_config_byte(dev, 0x76, b ^ 0x40);

			dev_info(&dev->dev, "Disabling VIA CX700 PCI parking\n");
		}
	}

	if (pci_read_config_byte(dev, 0x72, &b) == 0) {
		if (b != 0) {

			pci_write_config_byte(dev, 0x72, 0x0);


			pci_write_config_byte(dev, 0x75, 0x1);


			pci_write_config_byte(dev, 0x77, 0x0);

			dev_info(&dev->dev, "Disabling VIA CX700 PCI caching\n");
		}
	}
}
