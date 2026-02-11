c3600_clear_irq(vm_instance_t *vm,u_int irq)
{
   c3600_t *router = VM_C3600(vm);
   cpu_mips_t *cpu0 = CPU_MIPS64(vm->boot_cpu);
   u_int slot,port;

   switch(irq) {
      case 0 ... 7:
         mips64_clear_irq(cpu0,irq);
         break;

      case C3600_NETIO_IRQ_BASE ... C3600_NETIO_IRQ_END:
         c3600_net_irq_get_slot_port(irq,&slot,&port);
         dev_c3600_iofpga_net_clear_irq(router->iofpga_data,slot,port);
         break;
   }
}
