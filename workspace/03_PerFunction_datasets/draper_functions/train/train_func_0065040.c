c7200_npe_set_type(c7200_t *router,char *npe_type)
{
   struct c7200_npe_driver *driver;

   if (router->vm->status == VM_STATUS_RUNNING) {
      vm_error(router->vm,"unable to change NPE type when online.\n");
      return(-1);
   }

   if (!(driver = c7200_npe_get_driver(npe_type))) {
      vm_error(router->vm,"unknown NPE type '%s'.\n",npe_type);
      return(-1);
   }

   router->npe_driver = driver;

   if (c7200_npe_set_eeprom(router) == -1) {
      vm_error(router->vm,"unable to find NPE '%s' EEPROM!\n",
               router->npe_driver->npe_type);
      return(-1);
   }

#if 0

   if (driver->iocard_required) {
      vm_slot_add_binding(router->vm,"C7200-IO-FE",0,0);
      vm_slot_set_flag(router->vm,0,0,CISCO_CARD_FLAG_OVERRIDE);
   }
#endif
   c7200_refresh_systemid(router);
   return(0);
}
