c7200_set_slot_eeprom(c7200_t *router,u_int slot,
                          struct cisco_eeprom *eeprom)
{
   if (slot >= C7200_MAX_PA_BAYS)
      return(-1);

   switch(slot) {

      case 0:
         router->pa_eeprom_g1.eeprom[0] = eeprom;
         break;
      case 1:
         router->pa_eeprom_g1.eeprom[1] = eeprom;
         break;
      case 3:
         router->pa_eeprom_g1.eeprom[2] = eeprom;
         break;
      case 4:
         router->pa_eeprom_g1.eeprom[3] = eeprom;
         break;


      case 2:
         router->pa_eeprom_g2.eeprom[0] = eeprom;
         break;
      case 5:
         router->pa_eeprom_g2.eeprom[1] = eeprom;
         break;
      case 6:
         router->pa_eeprom_g2.eeprom[2] = eeprom;
         break;


      case 7:
         router->pa_eeprom_g3.eeprom[0] = eeprom;
         break;
   }

   return(0);
}
