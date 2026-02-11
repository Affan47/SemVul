dev_c7200_pa_a1_init(vm_instance_t *vm,struct cisco_card *card)
{
   u_int slot = card->slot_id;
   struct pci_device *pci_dev_ti,*pci_dev_plx;
   struct pa_a1_data *d;
   struct vdevice *dev;
   m_uint8_t *p;


   if (!(d = malloc(sizeof(*d)))) {
      vm_error(vm,"%s: out of memory\n",card->dev_name);
      return(-1);
   }

   memset(d,0,sizeof(*d));


   card->pci_bus = vm->slots_pci_bus[slot];


   cisco_card_set_eeprom(vm,card,cisco_eeprom_find_pa("PA-A1"));
   c7200_set_slot_eeprom(VM_C7200(vm),slot,&card->eeprom);


   pci_dev_ti = pci_dev_add(card->pci_bus,card->dev_name,
                            TI1570_PCI_VENDOR_ID,TI1570_PCI_PRODUCT_ID,
                            0,0,c7200_net_irq_for_slot_port(slot,0),d,
                            NULL,pci_ti1570_read,pci_ti1570_write);

   if (!pci_dev_ti) {
      vm_error(vm,"%s: unable to create PCI device TI1570.\n",
               card->dev_name);
      return(-1);
   }


   pci_dev_plx = pci_dev_add(card->pci_bus,card->dev_name,
                             PLX_9060ES_PCI_VENDOR_ID,
                             PLX_9060ES_PCI_PRODUCT_ID,
                             1,0,-1,d,
                             NULL,pci_plx9060es_read,pci_plx9060es_write);

   if (!pci_dev_plx) {
      vm_error(vm,"%s: unable to create PCI device PLX 9060ES.\n",
               card->dev_name);
      return(-1);
   }


   d->name        = card->dev_name;
   d->vm          = vm;
   d->pci_dev_ti  = pci_dev_ti;
   d->pci_dev_plx = pci_dev_plx;


   if (!(d->ctrl_mem_ptr = malloc(TI1570_CTRL_MEM_SIZE))) {
      vm_error(vm,"%s: unable to create control memory.\n",card->dev_name);
      return(-1);
   }


   p = (m_uint8_t *)d->ctrl_mem_ptr;

   d->iregs = (m_uint32_t *)(p + TI1570_INTERNAL_REGS_OFFSET);
   d->tx_sched_table = (m_uint32_t *)(p + TI1570_TX_SCHED_OFFSET);
   d->tx_dma_table = (ti1570_tx_dma_entry_t *)(p + TI1570_TX_DMA_TABLE_OFFSET);
   d->rx_vpi_vci_dma_table = (m_uint32_t *)(p+TI1570_RX_DMA_PTR_TABLE_OFFSET);
   d->rx_dma_table = (ti1570_rx_dma_entry_t *)(p + TI1570_RX_DMA_TABLE_OFFSET);
   d->rx_fbr_table = (ti1570_rx_fbr_entry_t *)(p + TI1570_FREE_BUFFERS_OFFSET);

   ti1570_reset(d,TRUE);


   if (!(dev = dev_create(card->dev_name))) {
      vm_error(vm,"%s: unable to create device.\n",card->dev_name);
      return(-1);
   }

   dev->phys_addr = 0;
   dev->phys_len  = 0x200000;
   dev->handler   = dev_pa_a1_access;


   dev->priv_data = d;
   d->dev = dev;


   card->drv_info = d;
   return(0);
}
