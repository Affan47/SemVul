cb_edit_cats(GtkWidget *widget, gpointer data)
{
   struct ExpenseAppInfo ai;
   char full_name[256];
   char buffer[65536];
   int num;
   size_t size;
   void *buf;
   struct pi_file *pf;

   jp_logf(JP_LOG_DEBUG, "cb_edit_cats\n");

   jp_get_home_file_name("ExpenseDB.pdb", full_name, 250);

   buf=NULL;
   memset(&ai, 0, sizeof(ai));

   pf = pi_file_open(full_name);
   pi_file_get_app_info(pf, &buf, &size);

   num = unpack_ExpenseAppInfo(&ai, buf, size);
   if (num <= 0) {
      jp_logf(JP_LOG_WARN, _("Error reading file: %s\n"), "ExpenseDB.pdb");
      return;
   }

   pi_file_close(pf);

   jp_edit_cats(widget, "ExpenseDB", &(ai.category));

   size = pack_ExpenseAppInfo(&ai, (unsigned char *)buffer, 65535);

   jp_pdb_file_write_app_block("ExpenseDB", buffer, size);


   plugin_gui_refresh(-1);
}
