cb_import_select_row(GtkWidget *file_clist,
                                 gint row,
                                 gint column,
                                 GdkEventButton *bevent,
                                 gpointer data)
{
   const char *sel;
   struct stat statb;
   int guessed_type;
   int i;

   jp_logf(JP_LOG_DEBUG, "cb_import_select_row\n");
   sel = gtk_file_selection_get_filename(GTK_FILE_SELECTION(filew));


   if (stat(sel, &statb)) {
      jp_logf(JP_LOG_DEBUG, "File selected was not stat-able\n");
      return;
   }
   if (!S_ISREG(statb.st_mode)) {
      jp_logf(JP_LOG_DEBUG, "File selected was not a regular file\n");
      return;
   }

   guessed_type=guess_file_type(sel);
   for (i=0; i<MAX_IMPORT_TYPES; i++) {
      if (radio_types[i]==NULL) break;
      if (guessed_type==radio_file_types[i]) {
         gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_types[i]), TRUE);
         break;
      }
   }

   return;
}
