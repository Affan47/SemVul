gtk_cmclist_set_column_visibility (GtkCMCList *clist,
				 gint      column,
				 gboolean  visible)
{
  cm_return_if_fail (GTK_IS_CMCLIST (clist));

  if (column < 0 || column >= clist->columns)
    return;
  if (clist->column[column].visible == visible)
    return;


  if (!visible)
    {
      gint i;
      gint vis_columns = 0;

      for (i = 0, vis_columns = 0; i < clist->columns && vis_columns < 2; i++)
	if (clist->column[i].visible)
	  vis_columns++;

      if (vis_columns < 2)
	return;
    }

  clist->column[column].visible = visible;

  if (clist->column[column].button)
    {
      if (visible)
	gtk_widget_show (clist->column[column].button);
      else
	gtk_widget_hide (clist->column[column].button);
    }

  gtk_widget_queue_resize (GTK_WIDGET(clist));
}
