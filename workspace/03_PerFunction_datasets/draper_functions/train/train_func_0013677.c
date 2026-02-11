cb_export_browse_ok(GtkWidget *widget, gpointer data)
{
   const char *sel;

   glob_export_browse_pressed=BROWSE_OK;
   if (glob_pref_export) {
      sel = gtk_file_selection_get_filename(GTK_FILE_SELECTION(data));
      set_pref(glob_pref_export, 0, sel, TRUE);
   }
   gtk_widget_destroy(data);
}
