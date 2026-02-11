show_entry(GtkWidget *widget, gpointer data)
{
 gchar *text;
 GtkSheet *sheet;
 GtkWidget *sheet_entry = NULL;
 gint cur_page;

 if(!GTK_WIDGET_HAS_FOCUS(widget)) {
   return;
 }

 cur_page = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook));

 sheet = GTK_SHEET(sheets[cur_page]);
 if (sheet != NULL) {
   sheet_entry = gtk_sheet_get_entry( GTK_SHEET(sheet) );
 }


 if (entry != NULL) {
   text = (gchar *) gtk_entry_get_text (GTK_ENTRY(sheet_entry));
   if( text != NULL ) {
     gtk_entry_set_text(GTK_ENTRY(entry),  text);
   }
   else {
     gtk_entry_set_text(GTK_ENTRY(entry), (const gchar *) "");

   }
 }
}
