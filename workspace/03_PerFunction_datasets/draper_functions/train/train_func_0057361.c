set_x_align (ClutterBinLayout    *self,
             ClutterBinAlignment  alignment)
{
  ClutterBinLayoutPrivate *priv = self->priv;

  if (priv->x_align != alignment)
    {
      ClutterLayoutManager *manager;

      priv->x_align = alignment;

      manager = CLUTTER_LAYOUT_MANAGER (self);
      clutter_layout_manager_layout_changed (manager);

      g_object_notify_by_pspec (G_OBJECT (self), bin_props[PROP_X_ALIGN]);
    }
}
