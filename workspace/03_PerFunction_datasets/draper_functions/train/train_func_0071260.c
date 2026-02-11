gtk_cmclist_set_row_style (GtkCMCList *clist,
			 gint      row,
			 GtkStyle *style)
{
  GtkRequisition requisition;
  GtkCMCListRow *clist_row;
  gint *old_width;
  gint i;

  cm_return_if_fail (GTK_IS_CMCLIST (clist));

  if (row < 0 || row >= clist->rows)
    return;

  clist_row = ROW_ELEMENT (clist, row)->data;

  if (clist_row->style == style)
    return;

  old_width = g_new (gint, clist->columns);

  if (!GTK_CMCLIST_AUTO_RESIZE_BLOCKED (clist))
    {
      for (i = 0; i < clist->columns; i++)
	if (clist->column[i].auto_resize)
	  {
	    GTK_CMCLIST_GET_CLASS (clist)->cell_size_request (clist, clist_row,
							   i, &requisition);
	    old_width[i] = requisition.width;
	  }
    }

  if (clist_row->style)
    {
      if (gtk_widget_get_realized (GTK_WIDGET(clist)))
        gtk_style_detach (clist_row->style);
      g_object_unref (clist_row->style);
    }

  clist_row->style = style;

  if (clist_row->style)
    {
      g_object_ref (clist_row->style);

      if (gtk_widget_get_realized (GTK_WIDGET(clist)))
        clist_row->style = gtk_style_attach (clist_row->style,
					     clist->clist_window);
    }

  if (GTK_CMCLIST_AUTO_RESIZE_BLOCKED (clist))
    for (i = 0; i < clist->columns; i++)
      column_auto_resize (clist, clist_row, i, old_width[i]);

  g_free (old_width);


  if (CLIST_UNFROZEN (clist))
    {
      if (gtk_cmclist_row_is_visible (clist, row) != GTK_VISIBILITY_NONE)
	GTK_CMCLIST_GET_CLASS (clist)->draw_row (clist, NULL, row, clist_row);
    }
}
