exo_icon_view_allocate_children (ExoIconView *icon_view)
{
  const ExoIconViewPrivate *priv = icon_view->priv;
  const ExoIconViewChild   *child;
  GtkAllocation             allocation;
  const GList              *lp;
  gint                      focus_line_width;
  gint                      focus_padding;

  for (lp = priv->children; lp != NULL; lp = lp->next)
    {
      child = EXO_ICON_VIEW_CHILD (lp->data);


      if (child->cell < 0)
        allocation = child->item->area;
      else
        allocation = child->item->box[child->cell];


      gtk_widget_style_get (GTK_WIDGET (icon_view), "focus-line-width", &focus_line_width, "focus-padding", &focus_padding, NULL);
      allocation.x = MAX (0, allocation.x - (focus_line_width + focus_padding));
      allocation.y = MAX (0, allocation.y - (focus_line_width + focus_padding));
      allocation.width = MIN (priv->width - allocation.x, allocation.width + 2 * (focus_line_width + focus_padding));
      allocation.height = MIN (priv->height - allocation.y, allocation.height + 2 * (focus_line_width + focus_padding));


      gtk_widget_size_allocate (child->widget, &allocation);
    }
}
