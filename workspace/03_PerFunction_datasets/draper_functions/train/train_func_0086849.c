clutter_box_layout_pack (ClutterBoxLayout    *layout,
                         ClutterActor        *actor,
                         gboolean             expand,
                         gboolean             x_fill,
                         gboolean             y_fill,
                         ClutterBoxAlignment  x_align,
                         ClutterBoxAlignment  y_align)
{
  ClutterBoxLayoutPrivate *priv;
  ClutterLayoutManager *manager;
  ClutterLayoutMeta *meta;

  g_return_if_fail (CLUTTER_IS_BOX_LAYOUT (layout));
  g_return_if_fail (CLUTTER_IS_ACTOR (actor));

  priv = layout->priv;

  if (priv->container == NULL)
    {
      g_warning ("The layout of type '%s' must be associated to "
                 "a ClutterContainer before adding children",
                 G_OBJECT_TYPE_NAME (layout));
      return;
    }

  clutter_container_add_actor (priv->container, actor);

  manager = CLUTTER_LAYOUT_MANAGER (layout);
  meta = clutter_layout_manager_get_child_meta (manager,
                                                priv->container,
                                                actor);
  g_assert (CLUTTER_IS_BOX_CHILD (meta));

  box_child_set_align (CLUTTER_BOX_CHILD (meta), x_align, y_align);
  box_child_set_fill (CLUTTER_BOX_CHILD (meta), x_fill, y_fill);
  box_child_set_expand (CLUTTER_BOX_CHILD (meta), expand);
}
