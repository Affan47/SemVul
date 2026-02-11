pci_set_bus_of_node(struct pci_bus *bus)
{
	if (bus->self == NULL)
		bus->dev.of_node = pcibios_get_phb_of_node(bus);
	else
		bus->dev.of_node = of_node_get(bus->self->dev.of_node);
}
