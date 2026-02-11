gd_main_view_set_selection_mode (GdMainView *self,
                                 gboolean selection_mode)
{
  if (selection_mode != self->priv->selection_mode)
    {
      self->priv->selection_mode = selection_mode;
      gd_main_view_apply_selection_mode (self);
      g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_SELECTION_MODE]);
    }
}
