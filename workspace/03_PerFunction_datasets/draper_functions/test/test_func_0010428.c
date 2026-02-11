pci_setup_bridge_mmio(struct pci_dev *bridge)
{
	struct resource *res;
	struct pci_bus_region region;
	u32 l;


	res = &bridge->resource[PCI_BRIDGE_RESOURCES + 1];
	pcibios_resource_to_bus(bridge->bus, &region, res);
	if (res->flags & IORESOURCE_MEM) {
		l = (region.start >> 16) & 0xfff0;
		l |= region.end & 0xfff00000;
		dev_info(&bridge->dev, "  bridge window %pR\n", res);
	} else {
		l = 0x0000fff0;
	}
	pci_write_config_dword(bridge, PCI_MEMORY_BASE, l);
}
