window_alignment(struct pci_bus *bus,
					unsigned long type)
{
	resource_size_t align = 1, arch_align;

	if (type & IORESOURCE_MEM)
		align = PCI_P2P_DEFAULT_MEM_ALIGN;
	else if (type & IORESOURCE_IO) {


		if (bus->self->io_window_1k)
			align = PCI_P2P_DEFAULT_IO_ALIGN_1K;
		else
			align = PCI_P2P_DEFAULT_IO_ALIGN;
	}

	arch_align = pcibios_window_alignment(bus, type);
	return max(align, arch_align);
}
