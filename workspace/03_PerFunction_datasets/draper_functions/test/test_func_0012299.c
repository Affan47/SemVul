mx_offscreen_dispose (GObject *object)
{
  MxOffscreen *self = MX_OFFSCREEN (object);
  MxOffscreenPrivate *priv = self->priv;

  priv->in_dispose = TRUE;

  if (priv->child &&
      (clutter_actor_get_parent (priv->child) != (ClutterActor *)self))
    mx_offscreen_set_child (self, NULL);

  if (priv->fbo)
    {
      cogl_handle_unref (priv->fbo);
      priv->fbo = NULL;
    }

  if (priv->acc_material)
    {
      cogl_handle_unref (priv->acc_material);
      priv->acc_material = NULL;
    }

  if (priv->acc_fbo)
    {
      cogl_handle_unref (priv->acc_fbo);
      priv->acc_fbo = NULL;
    }

  G_OBJECT_CLASS (mx_offscreen_parent_class)->dispose (object);
}
