dev_c3660_iofpga_net_update_irq(struct c3600_iofpga_data *d)
{
   if (d->net_irq_status[0] || d->net_irq_status[1]) {
      vm_set_irq(d->router->vm,C3600_NETIO_IRQ);
   } else {
      vm_clear_irq(d->router->vm,C3600_NETIO_IRQ);
   }
}
