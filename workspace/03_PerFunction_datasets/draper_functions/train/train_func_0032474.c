cb_quit(GtkWidget *widget, gpointer data)
{
   const char *sel;
   char dir[MAX_PREF_LEN+2];
   int i;

   jp_logf(JP_LOG_DEBUG, "Quit\n");

   sel = gtk_file_selection_get_filename(GTK_FILE_SELECTION(filew));
   strncpy(dir, sel, MAX_PREF_LEN);
   dir[MAX_PREF_LEN]='\0';
   i=strlen(dir)-1;
   if (i<0) i=0;
   if (dir[i]!='/') {
      for (i=strlen(dir); i>=0; i--) {
         if (dir[i]=='/') {
            dir[i+1]='\0';
            break;
         }
      }
   }

   set_pref(PREF_MEMO_IMPORT_PATH, 0, dir, TRUE);

   filew = NULL;
   gtk_widget_destroy(data);
}
