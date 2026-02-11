pci_bus_remove(struct pci_bus *pci_bus)
{
   struct pci_device *dev,*next;
   struct pci_bridge *bridge,*next_bridge;

   if (pci_bus) {

      for(dev=pci_bus->dev_list;dev;dev=next) {
         next = dev->next;
         free(dev);
      }


      for(bridge=pci_bus->bridge_list;bridge;bridge=next_bridge) {
         next_bridge = bridge->next;
         free(bridge);
      }


      free(pci_bus->name);
      free(pci_bus);
   }
}
