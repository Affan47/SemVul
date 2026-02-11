decode_bar(struct pci_dev *dev, u32 bar)
{
	u32 mem_type;
	unsigned long flags;

	if ((bar & PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_IO) {
		flags = bar & ~PCI_BASE_ADDRESS_IO_MASK;
		flags |= IORESOURCE_IO;
		return flags;
	}

	flags = bar & ~PCI_BASE_ADDRESS_MEM_MASK;
	flags |= IORESOURCE_MEM;
	if (flags & PCI_BASE_ADDRESS_MEM_PREFETCH)
		flags |= IORESOURCE_PREFETCH;

	mem_type = bar & PCI_BASE_ADDRESS_MEM_TYPE_MASK;
	switch (mem_type) {
	case PCI_BASE_ADDRESS_MEM_TYPE_32:
		break;
	case PCI_BASE_ADDRESS_MEM_TYPE_1M:

		break;
	case PCI_BASE_ADDRESS_MEM_TYPE_64:
		flags |= IORESOURCE_MEM_64;
		break;
	default:

		break;
	}
	return flags;
}
