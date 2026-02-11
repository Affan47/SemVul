keyr_plugin_unpack_cai_from_ai(struct CategoryAppInfo *cai,
                                          unsigned char *record,
                                          int len)
{
   int i, rec;

   jp_logf(JP_LOG_DEBUG, "unpack_keyring_cai_from_ai\n");

   if (len < 2 + 16 * 16 + 16 + 2)
      return EXIT_FAILURE;
   rec = get_short(record);
   for (i = 0; i < 16; i++) {
      if (rec & (1 << i))
         cai->renamed[i] = 1;
      else
         cai->renamed[i] = 0;
   }
   record += 2;
   for (i = 0; i < 16; i++) {
      memcpy(cai->name[i], record, 16);
      record += 16;
   }
   memcpy(cai->ID, record, 16);
   record += 16;
   cai->lastUniqueID = get_byte(record);

   return EXIT_SUCCESS;
}
