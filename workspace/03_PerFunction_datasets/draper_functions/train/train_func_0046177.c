gd_header_bar_compute_size_for_orientation (GtkWidget *widget,
                                            gint       avail_size,
                                            gint      *minimum_size,
                                            gint      *natural_size)
{
  GdHeaderBar *bar = GD_HEADER_BAR (widget);
  GdHeaderBarPrivate *priv = bar->priv;
  GList *children;
  gint required_size = 0;
  gint required_natural = 0;
  gint child_size;
  gint child_natural;
  gint nvis_children;
  GtkBorder css_borders;

  avail_size -= 2 * priv->vpadding;

  nvis_children = 0;

  for (children = priv->children; children != NULL; children = children->next)
    {
      Child *child = children->data;

      if (gtk_widget_get_visible (child->widget))
        {
          gtk_widget_get_preferred_width_for_height (child->widget,
                                                     avail_size, &child_size, &child_natural);

          required_size += child_size;
          required_natural += child_natural;

          nvis_children += 1;
        }
    }

  gtk_widget_get_preferred_width (priv->labels_sizing_box,
                                  &child_size, &child_natural);
  required_size += child_size;
  required_natural += child_natural;

  if (nvis_children > 0)
    {
      required_size += nvis_children * priv->spacing;
      required_natural += nvis_children * priv->spacing;
    }

  get_css_padding_and_border (widget, &css_borders);

  required_size += 2 * priv->hpadding + css_borders.left + css_borders.right;
  required_natural += 2 * priv->hpadding + css_borders.left + css_borders.right;

  if (minimum_size)
    *minimum_size = required_size;

  if (natural_size)
    *natural_size = required_natural;
}
