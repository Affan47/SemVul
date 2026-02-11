exo_wrap_table_get_max_child_size (const ExoWrapTable *table,
                                   gint               *max_width_return,
                                   gint               *max_height_return)
{
  GtkRequisition child_requisition;
  GtkWidget     *child;
  GList         *lp;
  gint           max_width = 0;
  gint           max_height = 0;
  gint           num_children = 0;

  for (lp = table->priv->children; lp != NULL; lp = lp->next)
    {
      child = GTK_WIDGET (lp->data);
      if (GTK_WIDGET_VISIBLE (child))
        {
          gtk_widget_size_request (child, &child_requisition);
          if (child_requisition.width > max_width)
            max_width = child_requisition.width;
          if (child_requisition.height > max_height)
            max_height = child_requisition.height;


          ++num_children;
        }
    }


  if (G_LIKELY (num_children > 0))
    {
      if (G_UNLIKELY (max_width < 1))
        max_width = 1;
      if (G_UNLIKELY (max_height < 1))
        max_height = 1;
    }


  if (G_LIKELY (max_width_return != NULL))
    *max_width_return = max_width;
  if (G_LIKELY (max_height_return != NULL))
    *max_height_return = max_height;

  return num_children;
}
