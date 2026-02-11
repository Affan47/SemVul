get_contact_app_info(struct ContactAppInfo *ai)
{
   int num, r;
   int rec_size;
   unsigned char *buf;
   pi_buffer_t pi_buf;
   long char_set;

   memset(ai, 0, sizeof(*ai));

   strcpy(ai->category.name[0], "Unfiled");

   r = jp_get_app_info("ContactsDB-PAdd", &buf, &rec_size);
   if ((r != EXIT_SUCCESS) || (rec_size<=0)) {
      jp_logf(JP_LOG_WARN, _("%s:%d Error reading application info %s\n"), __FILE__, __LINE__, "ContactsDB-PAdd");
      if (buf) {
         free(buf);
      }
      return EXIT_FAILURE;
   }

   pi_buf.data = buf;
   pi_buf.used = rec_size;
   pi_buf.allocated = rec_size;

   num = jp_unpack_ContactAppInfo(ai, &pi_buf);
   if (buf) {
      free(buf);
   }
   if ((num<0) || (rec_size<=0)) {
      jp_logf(JP_LOG_WARN, _("Error reading file: %s\n"), "ContactsDB-PAdd.pdb");
      return EXIT_FAILURE;
   }

   get_pref(PREF_CHAR_SET, &char_set, NULL);
   if (char_set != CHAR_SET_LATIN1) {

      int i;

      for (i = 0; i < 49 + 3; i++)
         if (ai->labels[i][0] != '\0') {
            charset_p2j(ai->labels[i], 16, char_set);
         }
      for (i = 0; i < 8; i++)
         if (ai->phoneLabels[i][0] != '\0') {
            charset_p2j(ai->phoneLabels[i], 16, char_set);
         }
      for (i = 0; i < 3; i++)
         if (ai->addrLabels[i][0] != '\0') {
            charset_p2j(ai->addrLabels[i], 16, char_set);
         }
      for (i = 0; i < 5; i++)
         if (ai->IMLabels[i][0] != '\0') {
            charset_p2j(ai->IMLabels[i], 16, char_set);
         }
   }

   return EXIT_SUCCESS;
}
