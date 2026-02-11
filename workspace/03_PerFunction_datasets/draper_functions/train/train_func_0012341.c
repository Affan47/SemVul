gd_revealer_real_get_preferred_height (GtkWidget* widget,
                                       gint* minimum_height_out,
                                       gint* natural_height_out)
{
  GdRevealer *revealer = GD_REVEALER (widget);
  GdRevealerPrivate *priv = revealer->priv;
  gint minimum_height;
  gint natural_height;

  GTK_WIDGET_CLASS (gd_revealer_parent_class)->get_preferred_height (widget, &minimum_height, &natural_height);

  if (priv->orientation == GTK_ORIENTATION_HORIZONTAL)
    natural_height = round (natural_height * priv->current_pos);

  minimum_height = natural_height;

  if (minimum_height_out)
    *minimum_height_out = minimum_height;
  if (natural_height_out)
    *natural_height_out = natural_height;
}
