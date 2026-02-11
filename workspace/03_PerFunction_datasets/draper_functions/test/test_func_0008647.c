games_grid_frame_size_allocate (GtkWidget * widget,
				GtkAllocation * allocation)
{
  GamesGridFrame *frame = GAMES_GRID_FRAME (widget);
  GtkWidget *child = gtk_bin_get_child (GTK_BIN (widget));
  GtkAllocation child_allocation;
  gint xsize, ysize, size;

  gtk_widget_set_allocation (widget, allocation);

  xsize = MAX (1, (allocation->width - frame->priv->xpadding) / frame->priv->xmult);
  ysize = MAX (1, (allocation->height - frame->priv->ypadding) / frame->priv->ymult);

  size = MIN (xsize, ysize);

  child_allocation.width = size * frame->priv->xmult + frame->priv->xpadding;
  child_allocation.height = size * frame->priv->ymult + frame->priv->ypadding;

  child_allocation.x =
    (allocation->width - child_allocation.width) * frame->priv->xalign +
    allocation->x;
  child_allocation.y =
    (allocation->height - child_allocation.height) * frame->priv->yalign +
    allocation->y;

  if (gtk_widget_get_mapped (widget) &&
      (child_allocation.x != frame->priv->old_allocation.x ||
       child_allocation.y != frame->priv->old_allocation.y ||
       child_allocation.width != frame->priv->old_allocation.width ||
       child_allocation.height != frame->priv->old_allocation.height))
    gdk_window_invalidate_rect (gtk_widget_get_window (widget), allocation, FALSE);

  if (child && gtk_widget_get_visible (child))
    gtk_widget_size_allocate (child, &child_allocation);

  frame->priv->old_allocation = child_allocation;
}
