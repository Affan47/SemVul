cb_export_browse(GtkWidget *widget, gpointer data)
{
   int r;
   const char *svalue;

   r = export_browse(GTK_WIDGET(data), glob_pref_export);
   if (r==BROWSE_OK) {
      if (glob_pref_export) {
         get_pref(glob_pref_export, NULL, &svalue);
         gtk_entry_set_text(GTK_ENTRY(save_as_entry), svalue);
      }
   }
}
