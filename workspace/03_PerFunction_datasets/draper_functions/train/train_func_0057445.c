st_scroll_bar_get_preferred_height (ClutterActor *self,
                                    gfloat        for_width,
                                    gfloat       *min_height_p,
                                    gfloat       *natural_height_p)
{
  StScrollBar *bar = ST_SCROLL_BAR (self);
  StScrollBarPrivate *priv = bar->priv;
  StThemeNode *theme_node = st_widget_get_theme_node (ST_WIDGET (self));
  gfloat trough_min_height, trough_natural_height;
  gfloat handle_min_height, handle_natural_height;

  st_theme_node_adjust_for_width (theme_node, &for_width);

  _st_actor_get_preferred_height (priv->trough, for_width, TRUE,
                                  &trough_min_height, &trough_natural_height);

  _st_actor_get_preferred_height (priv->handle, for_width, TRUE,
                                  &handle_min_height, &handle_natural_height);

  if (priv->vertical)
    {
      if (min_height_p)
        *min_height_p = trough_min_height + handle_min_height;

      if (natural_height_p)
        *natural_height_p = trough_natural_height + handle_natural_height;
    }
  else
    {
      if (min_height_p)
        *min_height_p = MAX (trough_min_height, handle_min_height);

      if (natural_height_p)
        *natural_height_p = MAX (trough_natural_height, handle_natural_height);
    }

  st_theme_node_adjust_preferred_height (theme_node, min_height_p, natural_height_p);
}
