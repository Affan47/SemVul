cb_dialog_button(GtkWidget *widget, gpointer data)
{
   struct dialog_data *Pdata;
   GtkWidget *w;


   w = GTK_WIDGET(gtk_widget_get_toplevel(widget));

   if (GTK_IS_WINDOW(w)) {
      Pdata = gtk_object_get_data(GTK_OBJECT(w), "dialog_data");
      if (Pdata) {
         Pdata->button_hit = GPOINTER_TO_INT(data);
      }
      gtk_widget_destroy(GTK_WIDGET(w));
   }
}
