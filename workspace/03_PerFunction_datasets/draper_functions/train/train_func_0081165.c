pci_bridge_map_bus(struct pci_bridge *bridge,struct pci_bus *pci_bus)
{
   if (bridge != NULL) {
      bridge->pci_bus = pci_bus;

      if (bridge->pci_bus != NULL)
         bridge->pci_bus->bus = bridge->sec_bus;
   }
}
