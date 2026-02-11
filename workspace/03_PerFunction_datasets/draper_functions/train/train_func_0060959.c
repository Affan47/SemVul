cb_install_user_button(GtkWidget *widget, gpointer data)
{
   GtkWidget *w;
   struct install_dialog_data *Pdata;

   w = gtk_widget_get_toplevel(widget);
   Pdata = gtk_object_get_data(GTK_OBJECT(w), "install_dialog_data");
   if (Pdata) {
      Pdata->button_hit = GPOINTER_TO_INT(data);
      if (Pdata->button_hit == DIALOG_SAID_1) {
         g_strlcpy(Pdata->user,
               gtk_entry_get_text(GTK_ENTRY(Pdata->user_entry)),
               sizeof(Pdata->user));
         sscanf(gtk_entry_get_text(GTK_ENTRY(Pdata->ID_entry)), "%lu",
                &(Pdata->id));
      }
   }

   gtk_widget_destroy(w);
}
