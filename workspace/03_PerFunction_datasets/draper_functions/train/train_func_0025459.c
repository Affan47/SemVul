send_button_send (GtkWidget *widget, gpointer data)
{
  int i, n;
  gchar *fname;
  const gchar *addr;
  const gchar *comment;
  char **files;
  GList *selection;

  addr = gtk_entry_get_text (GTK_ENTRY(((struct s_send_data *) data)->addrinput->entry));
  comment = gtk_entry_get_text (GTK_ENTRY(((struct s_send_data *) data)->comment));

  if (send_history_add (addr, ((struct s_send_data *) data)->addrinput)) {
    gtk_combo_set_popdown_strings (GTK_COMBO(((struct s_send_data *) data)->wdata->addrinput), config.addrs);
    gtk_entry_set_text (GTK_ENTRY(GTK_COMBO((((struct s_send_data *) data)->wdata)->addrinput)->entry), "");
  }

  for (selection = GTK_CLIST(((struct s_send_data *) data)->listbox)->selection, n=0;
       selection;
       selection = selection->next)
      n++;

  if (n>0 && (files = (char **)malloc ((n+1)*sizeof (char *))) != NULL) {
    memset (files, 0, (n+1)*sizeof (char *));
    for (selection = GTK_CLIST(((struct s_send_data *) data)->listbox)->selection, i=0;
	 selection;
	 selection = selection->next) {

      gtk_clist_get_text (GTK_CLIST(((struct s_send_data *) data)->listbox), (int)selection->data, 1, &fname);
      files[i++] = fname;
    }

    if (saft_send (addr, files, comment)) {
      send_button_unselect_all (widget, data);
      gtk_entry_set_text (GTK_ENTRY(((struct s_send_data *) data)->comment), "");
      free (files);
      if (config.closewindow)
	gtk_signal_emit_by_name (GTK_OBJECT (((struct s_send_data *) data)->dialog), "destroy");
    } else
      free (files);
  }
}
