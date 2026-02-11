c7200_pa_stop_online(vm_instance_t *vm,u_int slot,u_int subslot)
{
   if (!slot) {
      vm_error(vm,"OIR not supported on slot 0.\n");
      return(-1);
   }


   if (!vm_slot_get_card_ptr(vm,slot)) {
      vm_error(vm,"trying to shut down empty slot %u.\n",slot);
      return(-1);
   }


   vm_slot_disable_all_nio(vm,slot);


   c7200_trigger_oir_event(VM_C7200(vm),slot);


   vm_suspend(vm);


   if (vm_slot_shutdown(vm,slot) != 0)
      vm_error(vm,"unable to shutdown slot %u.\n",slot);


   vm_resume(vm);
   return(0);
}
