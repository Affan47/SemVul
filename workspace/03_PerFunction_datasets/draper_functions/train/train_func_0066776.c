receiver_row_select (GtkWidget *widget, gint row_select, gint column, GdkEventButton * event, gpointer data)
{
  gchar *sender;
  gchar *comment = NULL;
  char *s;

  gtk_clist_get_text (GTK_CLIST(((struct s_main_data *)data)->receiver), row_select, 5, &sender);
  gtk_clist_get_text (GTK_CLIST(((struct s_main_data *)data)->receiver), row_select, 6, &comment);

  if ((s = (char *)malloc(strlen(sender) + strlen(_("From: %s")))) == NULL)
    return FALSE;

  sprintf (s, _("From: %s"), sender);
  gtk_label_set_text (GTK_LABEL(((struct s_main_data *) data)->rinfo), s);

  if (comment)
    gtk_label_set_text (GTK_LABEL(((struct s_main_data *) data)->rcomment), strdup(comment));
  else
    gtk_label_set_text (GTK_LABEL(((struct s_main_data *) data)->rcomment), NULL);

  return FALSE;
}
