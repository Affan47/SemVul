dev_c7200_net_update_irq(c7200_t *router)
{
   int i,status = 0;

   for(i=0;i<3;i++)
      status |= router->net_irq_status[i] & router->net_irq_mask[i];

   if (status) {
      vm_set_irq(router->vm,C7200_NETIO_IRQ);
   } else {
      vm_clear_irq(router->vm,C7200_NETIO_IRQ);
   }
}
