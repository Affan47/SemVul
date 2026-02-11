c3725_set_slot_eeprom(c3725_t *router,u_int slot,
                          struct cisco_eeprom *eeprom)
{
   if ((slot < 1) || (slot >= C3725_MAX_NM_BAYS))
      return(-1);

   router->nm_eeprom_group[slot-1].eeprom[0] = eeprom;
   return(0);
}
