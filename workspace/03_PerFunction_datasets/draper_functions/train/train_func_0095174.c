vm_slot_save_config(vm_instance_t *vm,u_int slot_id,FILE *fd)
{
   struct cisco_card *card;
   int i;

   if (!(card = vm_slot_get_card_ptr(vm,slot_id)))
      return(-1);


   cisco_card_save_config(vm,card,fd);


   for(i=0;i<CISCO_CARD_MAX_SUBSLOTS;i++)
      cisco_card_save_config(vm,card->sub_slots[i],fd);

   return(0);
}
