main_button_select_all (GtkWidget *widget, gpointer data)
{
  int i;

  gtk_clist_freeze (GTK_CLIST(((struct s_main_data *) data)->listbox));

  for (i=1; i < GTK_CLIST(((struct s_main_data *) data)->listbox)->rows; i++) {
      gtk_clist_select_row (GTK_CLIST(((struct s_main_data *) data)->listbox), i, 0);
  }

  gtk_clist_thaw (GTK_CLIST(((struct s_main_data *) data)->listbox));
  gtk_widget_set_sensitive (((struct s_main_data *) data)->selectbutton, FALSE);
}
