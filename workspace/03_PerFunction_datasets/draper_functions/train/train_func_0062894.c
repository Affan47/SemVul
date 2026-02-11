cb_export_browse(GtkWidget *widget, gpointer data)
{
   int r;
   const char *svalue;

   r = export_browse(GTK_WIDGET(data), PREF_DATEBOOK_EXPORT_FILENAME);
   if (r==BROWSE_OK) {
      get_pref(PREF_DATEBOOK_EXPORT_FILENAME, NULL, &svalue);
      gtk_entry_set_text(GTK_ENTRY(save_as_entry), svalue);
   }
}
