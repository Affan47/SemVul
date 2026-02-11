cb_add(GtkWidget *widget, gpointer data)
{
   const char *sel;
   struct stat statb;

   jp_logf(JP_LOG_DEBUG, "install: cb_add\n");
   sel = gtk_file_selection_get_filename(GTK_FILE_SELECTION(data));
   jp_logf(JP_LOG_DEBUG, "file selected [%s]\n", sel);


   if (stat(sel, &statb)) {
      jp_logf(JP_LOG_DEBUG, "File selected was not stat-able\n");
      return;
   }
   if (!S_ISREG(statb.st_mode)) {
      jp_logf(JP_LOG_DEBUG, "File selected was not a regular file\n");
      return;
   }

   install_append_line(sel);
   install_update_clist();
}
