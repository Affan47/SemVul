button_receive (GtkWidget *widget, gpointer data)
{
  GList *selection;
  gchar *nr;
  gchar *fname;
  const gchar *dir;

  dir = gtk_entry_get_text (GTK_ENTRY(((struct s_main_data *) data)->rdirinput));

  gtk_clist_freeze (GTK_CLIST(((struct s_main_data *) data)->receiver));

  while ((selection = GTK_CLIST(((struct s_main_data *) data)->receiver)->selection)) {
    gtk_clist_get_text (GTK_CLIST(((struct s_main_data *) data)->receiver), (int)selection->data, 4, &nr);
    gtk_clist_get_text (GTK_CLIST(((struct s_main_data *) data)->receiver), (int)selection->data, 1, &fname);
    if (receive_file (nr, dir, fname))
      gtk_clist_remove (GTK_CLIST(((struct s_main_data *)data)->receiver), (int)selection->data);
    else
      gtk_clist_unselect_row (GTK_CLIST(((struct s_main_data *)data)->receiver), (int)selection->data, 0);
  }

  gtk_clist_thaw (GTK_CLIST(((struct s_main_data *) data)->receiver));
}
