pci_bus_show_dev_list(struct pci_bus *pci_bus)
{
   struct pci_device *dev;
   struct pci_bridge *bridge;
   char bus_id[32];

   if (!pci_bus)
      return;

   if (pci_bus->bus != -1) {
      snprintf(bus_id,sizeof(bus_id),"%2d",pci_bus->bus);
   } else {
      strcpy(bus_id,"XX");
   }

   for(dev=pci_bus->dev_list;dev;dev=dev->next) {
      printf("   %-18s: ID %4.4x:%4.4x, Bus %s, Dev. %2d, Func. %2d",
             dev->name,dev->vendor_id,dev->product_id,
             bus_id,dev->device,dev->function);

      if (dev->irq != -1)
         printf(", IRQ: %d\n",dev->irq);
      else
         printf("\n");
   }

   for(bridge=pci_bus->bridge_list;bridge;bridge=bridge->next)
      pci_bus_show_dev_list(bridge->pci_bus);
}
