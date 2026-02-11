clutter_grid_layout_insert_column (ClutterGridLayout *layout,
                                   gint               position)
{
  ClutterGridLayoutPrivate *priv;
  ClutterGridChild *grid_child;
  ClutterActorIter iter;
  ClutterActor *child;
  gint left, width;

  g_return_if_fail (CLUTTER_IS_GRID_LAYOUT (layout));

  priv = layout->priv;

  if (!priv->container)
    return;

  clutter_actor_iter_init (&iter, CLUTTER_ACTOR (priv->container));
  while (clutter_actor_iter_next (&iter, &child))
    {
      grid_child = GET_GRID_CHILD (layout, child);

      left = CHILD_LEFT (grid_child);
      width = CHILD_WIDTH (grid_child);

      if (left >= position)
        {
          CHILD_LEFT (grid_child) = left + 1;
          g_object_notify_by_pspec (G_OBJECT (grid_child),
                                    child_props[PROP_CHILD_LEFT_ATTACH]);
        }
      else if (left + width > position)
        {
          CHILD_WIDTH (grid_child) = width + 1;
          g_object_notify_by_pspec (G_OBJECT (grid_child),
                                    child_props[PROP_CHILD_WIDTH]);
        }
    }
  clutter_layout_manager_layout_changed (CLUTTER_LAYOUT_MANAGER (layout));
}
