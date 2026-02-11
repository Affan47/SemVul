bonobo_dock_item_handle_size_request (BonoboDockItem *item,
                                     GtkRequisition *requisition)
{
  GtkBin *bin;
  GtkContainer *container;

  bin = GTK_BIN (item);
  container = GTK_CONTAINER (item);

  if (bin->child != NULL)
    gtk_widget_size_request (bin->child, requisition);

  if (item->orientation == GTK_ORIENTATION_HORIZONTAL)
    requisition->width += DRAG_HANDLE_SIZE;
  else
    requisition->height += DRAG_HANDLE_SIZE;

  requisition->width += container->border_width * 2;
  requisition->height += container->border_width * 2;
}
