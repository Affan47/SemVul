vm_slot_check_eeprom(vm_instance_t *vm,u_int slot_id,u_int port_id)
{
   struct cisco_card *card,*rc;

   if (!(card = vm_slot_get_card_ptr(vm,slot_id)))
      return(FALSE);


   vm_slot_translate_port_id(vm,slot_id,port_id,&rc);

   if (rc == NULL)
      return(FALSE);

   return(cisco_card_check_eeprom(rc));
}
