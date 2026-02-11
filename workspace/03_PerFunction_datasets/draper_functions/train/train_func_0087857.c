vm_slot_show_drivers(vm_instance_t *vm)
{
   char *slot_type;
   int i;

   if (!vm->slots_drivers)
      return(-1);

   slot_type = cisco_card_get_type_desc(vm->slots_type);

   printf("Available %s %s drivers:\n",vm->platform->log_name,slot_type);

   for(i=0;vm->slots_drivers[i];i++) {
      printf("  * %s %s\n",
             vm->slots_drivers[i]->dev_type,
             !vm->slots_drivers[i]->supported ? "(NOT WORKING)" : "");
   }

   printf("\n");
   return(0);
}
