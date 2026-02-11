clutter_box_layout_set_homogeneous (ClutterBoxLayout *layout,
				    gboolean          homogeneous)
{
  ClutterBoxLayoutPrivate *priv;

  g_return_if_fail (CLUTTER_IS_BOX_LAYOUT (layout));

  priv = layout->priv;

  if (priv->is_homogeneous != homogeneous)
    {
      ClutterLayoutManager *manager;

      priv->is_homogeneous = !!homogeneous;

      manager = CLUTTER_LAYOUT_MANAGER (layout);

      clutter_layout_manager_layout_changed (manager);

      g_object_notify (G_OBJECT (layout), "homogeneous");
    }
}
