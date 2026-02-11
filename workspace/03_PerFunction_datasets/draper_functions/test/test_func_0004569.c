cb_dial_or_mail(GtkWidget *widget, gpointer data)
{
   GtkWidget *text;
   gchar *str;
   int is_mail;
   GtkTextIter    start_iter;
   GtkTextIter    end_iter;
   GtkTextBuffer *text_buffer;
   text=data;

   text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
   gtk_text_buffer_get_bounds(text_buffer,&start_iter,&end_iter);
   str = gtk_text_buffer_get_text(text_buffer,&start_iter,&end_iter,TRUE);

   if (!str) return;
   printf("[%s]\n", str);

   is_mail = GPOINTER_TO_INT(gtk_object_get_data(GTK_OBJECT(widget), "mail"));
   if (is_mail) {
      email_contact(widget, str);
   } else {
      dial_contact(widget, str);
   }

   g_free(str);
}
