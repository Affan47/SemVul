gtk_cmclist_set_column_widget (GtkCMCList  *clist,
			     gint       column,
			     GtkWidget *widget)
{
  gint new_button = 0;
  GtkWidget *old_widget;

  cm_return_if_fail (GTK_IS_CMCLIST (clist));

  if (column < 0 || column >= clist->columns)
    return;


  if (!clist->column[column].button)
    {
      column_button_create (clist, column);
      new_button = 1;
    }

  column_title_new (clist, column, NULL);


  old_widget = gtk_bin_get_child (GTK_BIN (clist->column[column].button));
  if (old_widget)
    gtk_container_remove (GTK_CONTAINER (clist->column[column].button),
			  old_widget);


  if (widget)
    {
      gtk_container_add (GTK_CONTAINER (clist->column[column].button), widget);
      gtk_widget_show (widget);
    }


  if (gtk_widget_get_visible (GTK_WIDGET(clist)) && new_button)
    size_allocate_title_buttons (clist);
}
