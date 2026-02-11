dev_plx9054_init(vm_instance_t *vm,char *name,
                           struct pci_bus *pci_bus,int pci_device,
                           struct vdevice *dev0,struct vdevice *dev1)
{
   struct plx_data *d;


   if (!(d = dev_plx_init(vm,name))) {
      fprintf(stderr,"PLX: unable to create device.\n");
      return NULL;
   }


   d->variant = 9054;
   d->plx_dev.handler = dev_plx9054_access;


   d->lspc[0].dev = dev0;
   d->lspc[1].dev = dev1;


   d->pci_plx_dev = pci_dev_add(pci_bus,name,
                                PLX_PCI_VENDOR_ID,PLX9054_PCI_PRODUCT_ID,
                                pci_device,0,-1,d,
                                NULL,pci_plx9054_read,pci_plx9054_write);

   if (!d->pci_plx_dev) {
      fprintf(stderr,"%s (PLX9054): unable to create PCI device.\n",name);
      goto err_pci_dev;
   }

   vm_object_add(vm,&d->vm_obj);
   return(&d->vm_obj);

 err_pci_dev:
   free(d);
   return NULL;
}
