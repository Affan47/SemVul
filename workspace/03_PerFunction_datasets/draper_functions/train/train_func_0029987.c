message_input_change (GObject *object, gpointer data)
{
  if (((struct s_main_data *) data)->addrok) {
    if (gtk_text_buffer_get_char_count(GTK_TEXT_BUFFER(object)) == 0) {
      ((struct s_main_data *) data)->addrok = 0;
      gtk_widget_set_sensitive (((struct s_main_data *) data)->msgsend, FALSE);
    }
  } else {
    if (gtk_text_buffer_get_char_count(GTK_TEXT_BUFFER(object)) > 0
	&& strlen(gtk_entry_get_text (GTK_ENTRY(GTK_COMBO(((struct s_main_data *) data)->addrinput)->entry))) > 0) {
      ((struct s_main_data *) data)->addrok = 1;
      gtk_widget_set_sensitive (((struct s_main_data *) data)->msgsend, TRUE);
    }
  }
}
