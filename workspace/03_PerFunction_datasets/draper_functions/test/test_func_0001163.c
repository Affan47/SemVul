pack_array_desc(array_desc *adesc)
{
   send_char_array((char *)adesc, sizeof(array_desc));
   if (adesc->type != NO_DATA_STORED && adesc->size > 0)
      send_int_array(adesc->list, adesc->size);
}
