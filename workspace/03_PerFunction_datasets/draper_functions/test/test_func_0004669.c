cisco_eeprom_v4_get_field(struct cisco_eeprom *eeprom,m_uint8_t *type,
                              m_uint8_t *len,size_t *offset)
{
   m_uint8_t tmp;


   if (cisco_eeprom_get_byte(eeprom,(*offset)++,type) == -1)
      return(-1);


   if (*type == 0xFF)
      return(0);


   tmp = (*type >> 6) & 0x03;

   if (tmp == 0x03) {

      if (cisco_eeprom_get_byte(eeprom,(*offset)++,&tmp) == -1)
         return(-1);

      *len = tmp & 0x0F;
   } else {

      *len = 1 << tmp;
   }

   return(1);
}
