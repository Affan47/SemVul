gtk_sheet_put(GtkSheet *sheet, GtkWidget *child, gint x, gint y)
{
  GtkRequisition child_requisition;
  GtkSheetChild *child_info;

  g_return_val_if_fail(sheet != NULL, NULL);
  g_return_val_if_fail(GTK_IS_SHEET(sheet), NULL);
  g_return_val_if_fail(child != NULL, NULL);
  g_return_val_if_fail(child->parent == NULL, NULL);

  child_info = g_new (GtkSheetChild, 1);
  child_info->widget = child;
  child_info->x = x;
  child_info->y = y;
  child_info->attached_to_cell = FALSE;
  child_info->floating = TRUE;
  child_info->xpadding = child_info->ypadding = 0;
  child_info->xexpand = child_info->yexpand = FALSE;
  child_info->xshrink = child_info->yshrink = FALSE;
  child_info->xfill = child_info->yfill = FALSE;

  sheet->children = g_list_append(sheet->children, child_info);

  gtk_widget_set_parent (child, GTK_WIDGET(sheet));

  gtk_widget_size_request(child, &child_requisition);

  if (GTK_WIDGET_VISIBLE(GTK_WIDGET(sheet)))
    {
       if(GTK_WIDGET_REALIZED(GTK_WIDGET(sheet)) &&
          (!GTK_WIDGET_REALIZED(child) || GTK_WIDGET_NO_WINDOW(child)))
        gtk_sheet_realize_child(sheet, child_info);

       if(GTK_WIDGET_MAPPED(GTK_WIDGET(sheet)) &&
          !GTK_WIDGET_MAPPED(child))
        gtk_widget_map(child);
    }

  gtk_sheet_position_child(sheet, child_info);


  if(GTK_WIDGET_REALIZED(GTK_WIDGET(sheet)))
   {
      if(sheet->row_titles_visible)
             gdk_window_show(sheet->row_title_window);
      if(sheet->column_titles_visible)
             gdk_window_show(sheet->column_title_window);
   }

  return (child_info);
}
