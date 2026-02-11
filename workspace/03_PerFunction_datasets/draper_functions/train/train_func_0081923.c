dev_c6sup1_iofpga_shutdown(vm_instance_t *vm,struct iofpga_data *d)
{
   if (d != NULL) {
      IOFPGA_LOCK(d);
      vm->vtty_con->read_notifier = NULL;
      vm->vtty_aux->read_notifier = NULL;
      IOFPGA_UNLOCK(d);


      ptask_remove(d->duart_irq_tid);


      dev_remove(vm,&d->dev);


      free(d);
   }
}
