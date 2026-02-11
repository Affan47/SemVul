c3600_init_platform(c3600_t *router)
{
   vm_instance_t *vm = router->vm;
   cpu_mips_t *cpu;
   cpu_gen_t *gen;
   vm_obj_t *obj;


   vm->conf_reg = vm->conf_reg_setup;


   vm_init_vtty(vm);


   vm->cpu_group = cpu_group_create("System CPU");


   if (!(gen = cpu_create(vm,CPU_TYPE_MIPS64,0))) {
      vm_error(vm,"unable to create CPU!\n");
      return(-1);
   }

   cpu = CPU_MIPS64(gen);


   cpu_group_add(vm->cpu_group,gen);
   vm->boot_cpu = gen;


   vm->set_irq = mips64_vm_set_irq;
   vm->clear_irq = mips64_vm_clear_irq;


   cpu->irq_idle_preempt[C3600_NETIO_IRQ] = TRUE;
   cpu->irq_idle_preempt[C3600_GT64K_IRQ] = TRUE;
   cpu->irq_idle_preempt[C3600_DUART_IRQ] = TRUE;


   cpu->idle_pc = vm->idle_pc;

   if (vm->timer_irq_check_itv)
      cpu->timer_irq_check_itv = vm->timer_irq_check_itv;


   if (!router->chassis_driver) {
      vm_error(vm,"no chassis defined.\n");
      return(-1);
   }


   dev_remote_control_init(vm,0x16000000,0x1000);


   dev_bootflash_init(vm,"bootflash","c3600-bootflash-8mb",
                      C3600_BOOTFLASH_ADDR);


   dev_nvram_init(vm,"nvram",
                  C3600_NVRAM_ADDR,vm->nvram_size*1024,&vm->conf_reg);


   dev_zero_init(vm,"zero",C3600_BITBUCKET_ADDR,0xc00000);


   if (dev_c3600_iofpga_init(router,C3600_IOFPGA_ADDR,0x40000) == -1)
      return(-1);

   if (!(obj = vm_object_find(router->vm,"io_fpga")))
      return(-1);

   router->iofpga_data = obj->data;


   if (!(vm->pci_io_space = pci_io_data_init(vm,C3600_PCI_IO_ADDR)))
      return(-1);


   if (router->chassis_driver->chassis_init(router) == -1)
      return(-1);


   vm_ram_init(vm,0x00000000ULL);


   if (!vm->rom_filename) {

      dev_rom_init(vm,"rom",C3600_ROM_ADDR,vm->rom_size*1048576,
                   mips64_microcode,mips64_microcode_len);
   } else {

      dev_ram_init(vm,"rom",TRUE,TRUE,NULL,FALSE,
                   C3600_ROM_ADDR,vm->rom_size*1048576);
   }


   dev_ns16552_init(vm,C3600_DUART_ADDR,0x1000,3,C3600_DUART_IRQ,
                    vm->vtty_con,vm->vtty_aux);


   dev_clpd6729_init(vm,vm->pci_bus[0],20,vm->pci_io_space,0x4402,0x4403);


   if (vm_slot_init_all(vm) == -1)
      return(-1);


   c3600_show_hardware(router);
   return(0);
}
