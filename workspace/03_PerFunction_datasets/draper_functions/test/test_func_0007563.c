get_preferred_width (BonoboDockItem *dock_item)
{
  GtkWidget *child;
  guint preferred_width;

  child = dock_item->_priv->child;

  if (!child)
    return 0;

  if (! check_guint_arg (G_OBJECT (child), "preferred_width", &preferred_width))
    {
      GtkRequisition child_requisition;

      gtk_widget_get_child_requisition (child, &child_requisition);
      preferred_width = child_requisition.width;
    }

  if (dock_item->orientation == GTK_ORIENTATION_HORIZONTAL)
    preferred_width += BONOBO_DOCK_ITEM_NOT_LOCKED (dock_item) ? DRAG_HANDLE_SIZE : 0;

  preferred_width += GTK_CONTAINER (dock_item)->border_width * 2;

  return preferred_width;
}
