dev_mueslix_update_irq_status(struct mueslix_data *d)
{
   if (d->irq_status & d->irq_mask)
      pci_dev_trigger_irq(d->vm,d->pci_dev);
   else {
      if (++d->irq_clearing_count == 3) {
         pci_dev_clear_irq(d->vm,d->pci_dev);
         d->irq_clearing_count = 0;
      }
   }
}
