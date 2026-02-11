st_table_get_preferred_height (ClutterActor *self,
                               gfloat        for_width,
                               gfloat       *min_height_p,
                               gfloat       *natural_height_p)
{
  gint *min_heights, *pref_heights;
  gfloat total_min_height, total_pref_height;
  StTablePrivate *priv = ST_TABLE (self)->priv;
  StThemeNode *theme_node = st_widget_get_theme_node (ST_WIDGET (self));
  gint i;
  gint *min_widths;
  ClutterActor *child;


  if (for_width < 0)
    {
      float natural_width;

      clutter_actor_get_preferred_width (self, -1, NULL, &natural_width);
      for_width = natural_width;
    }

  if (priv->n_rows < 1)
    {
      *min_height_p = 0;
      *natural_height_p = 0;
      return;
    }

  st_theme_node_adjust_for_width (theme_node, &for_width);


  g_array_set_size (priv->min_heights, 0);
  g_array_set_size (priv->pref_heights, 0);
  g_array_set_size (priv->min_heights, priv->n_rows);
  g_array_set_size (priv->pref_heights, priv->n_rows);


  min_widths = st_table_calculate_col_widths (ST_TABLE (self), for_width);

  min_heights = (gint *) priv->min_heights->data;
  pref_heights = (gint *) priv->pref_heights->data;


  for (child = clutter_actor_get_first_child (self);
       child != NULL;
       child = clutter_actor_get_next_sibling (child))
    {
      gint row, col, col_span, cell_width, row_span;
      gfloat min, pref;
      StTableChild *meta;

      meta = (StTableChild *) clutter_container_get_child_meta (CLUTTER_CONTAINER (self), child);

      if (!meta->allocate_hidden && !CLUTTER_ACTOR_IS_VISIBLE (child))
        continue;


      row = meta->row;
      col = meta->col;
      col_span = meta->col_span;
      row_span = meta->row_span;

      cell_width = 0;
      for (i = 0; i < col_span && col + i < priv->n_cols; i++)
        cell_width += min_widths[col + i];

      _st_actor_get_preferred_height (child, (float) cell_width, meta->x_fill,
                                      &min, &pref);

      if (row_span == 1 && min > min_heights[row])
        min_heights[row] = min;
      if (row_span == 1 && pref > pref_heights[row])
        pref_heights[row] = pref;
    }


  total_min_height = (priv->n_rows - 1) * (float) (priv->row_spacing);
  total_pref_height = total_min_height;

  for (i = 0; i < priv->n_rows; i++)
    {
      total_min_height += min_heights[i];
      total_pref_height += pref_heights[i];
    }

  if (min_height_p)
    *min_height_p = total_min_height;
  if (natural_height_p)
    *natural_height_p = total_pref_height;

  st_theme_node_adjust_preferred_height (theme_node, min_height_p, natural_height_p);
}
