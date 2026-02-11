column_auto_resize (GtkCMCList    *clist,
		    GtkCMCListRow *clist_row,
		    gint         column,
		    gint         old_width)
{

  GtkRequisition requisition;

  if (!clist->column[column].auto_resize ||
      GTK_CMCLIST_AUTO_RESIZE_BLOCKED (clist))
    return;

  if (clist_row)
    GTK_CMCLIST_GET_CLASS (clist)->cell_size_request (clist, clist_row,
						   column, &requisition);
  else
    requisition.width = 0;

  if (requisition.width > clist->column[column].width)
    gtk_cmclist_set_column_width (clist, column, requisition.width);
  else if (requisition.width < old_width &&
	   old_width == clist->column[column].width)
    {
      GList *list;
      gint new_width = 0;


      if (GTK_CMCLIST_SHOW_TITLES(clist) && clist->column[column].button)
    {
	gtk_widget_get_requisition (clist->column[column].button, &requisition);
	new_width = (requisition.width -
		     (CELL_SPACING + (2 * COLUMN_INSET)));
    }
      else
	new_width = 0;

      for (list = clist->row_list; list; list = list->next)
	{
	  GTK_CMCLIST_GET_CLASS (clist)->cell_size_request
	    (clist, GTK_CMCLIST_ROW (list), column, &requisition);
	  new_width = MAX (new_width, requisition.width);
	  if (new_width == clist->column[column].width)
	    break;
	}
      if (new_width < clist->column[column].width)
	gtk_cmclist_set_column_width
	  (clist, column, MAX (new_width, clist->column[column].min_width));
    }
}
