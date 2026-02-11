dev_c3600_nm_eth_shutdown(vm_instance_t *vm,struct cisco_card *card)
{
   struct nm_eth_data *data = card->drv_info;
   int i;


   cisco_card_unset_eeprom(card);
   c3600_set_slot_eeprom(VM_C3600(vm),card->slot_id,NULL);


   for(i=0;i<data->nr_port;i++)
      dev_am79c971_remove(data->port[i]);

   free(data);
   return(0);
}
