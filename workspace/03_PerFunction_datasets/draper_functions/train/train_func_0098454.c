clutter_grid_layout_set_row_spacing (ClutterGridLayout *layout,
                                     guint              spacing)
{
  ClutterGridLayoutPrivate *priv;

  g_return_if_fail (CLUTTER_IS_GRID_LAYOUT (layout));

  priv = layout->priv;

  if (COLUMNS (priv)->spacing != spacing)
    {
      COLUMNS (priv)->spacing = spacing;

      clutter_layout_manager_layout_changed (CLUTTER_LAYOUT_MANAGER (layout));
      g_object_notify_by_pspec (G_OBJECT (layout),
                                obj_props[PROP_ROW_SPACING]);
    }
}
