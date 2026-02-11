main_row_unselect (GtkWidget *widget, gint row_select, gint column, GdkEventButton * event, gpointer data)
{
  if (row_select > 0)
    gtk_widget_set_sensitive (((struct s_main_data *) data)->selectbutton, TRUE);

  return FALSE;
}
