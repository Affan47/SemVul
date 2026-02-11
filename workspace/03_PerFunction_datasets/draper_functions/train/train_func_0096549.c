button_set_use_markup (GdHeaderButton *self,
                       gboolean        use_markup)
{
  GdHeaderButtonPrivate *priv = GET_PRIVATE (self);

  if (priv->use_markup != use_markup)
    {
      priv->use_markup = use_markup;

      rebuild_child (self);
      g_object_notify (G_OBJECT (self), "use-markup");
    }
}
