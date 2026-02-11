userdsn_list_unselect (GtkWidget *widget, gint row, gint column,
    GdkEvent *event, TDSNCHOOSER *choose_t)
{
  if (choose_t)
    {
      gtk_widget_set_sensitive (choose_t->uremove, FALSE);
      gtk_widget_set_sensitive (choose_t->uconfigure, FALSE);
      gtk_widget_set_sensitive (choose_t->utest, FALSE);
    }
}
