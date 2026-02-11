divasa_get_pci_bar(unsigned char bus, unsigned char func,
				 int bar, void *pci_dev_handle)
{
	unsigned long ret = 0;
	struct pci_dev *dev = (struct pci_dev *) pci_dev_handle;

	if (bar < 6) {
		ret = dev->resource[bar].start;
	}

	DBG_TRC(("GOT BAR[%d]=%08x", bar, ret));

	{
		unsigned long type = (ret & 0x00000001);
		if (type & PCI_BASE_ADDRESS_SPACE_IO) {
			DBG_TRC(("  I/O"));
			ret &= PCI_BASE_ADDRESS_IO_MASK;
		} else {
			DBG_TRC(("  memory"));
			ret &= PCI_BASE_ADDRESS_MEM_MASK;
		}
		DBG_TRC(("  final=%08x", ret));
	}

	return (ret);
}
