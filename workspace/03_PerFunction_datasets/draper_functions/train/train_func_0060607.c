c3620_init(c3600_t *router)
{
   vm_instance_t *vm = router->vm;
   int i;


   mips64_set_prid(CPU_MIPS64(vm->boot_cpu),MIPS_PRID_R4700);


   if (c3600_init_gt64010(router) == -1)
      return(-1);


   for(i=0;i<C3600_MAX_NM_BAYS;i++)
      vm->slots_pci_bus[i] = vm->pci_bus[0];

   vm->elf_machine_id = C3620_ELF_MACHINE_ID;
   return(0);
}
