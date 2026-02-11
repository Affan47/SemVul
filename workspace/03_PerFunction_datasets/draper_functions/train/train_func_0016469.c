evd_web_selector_dispose (GObject *obj)
{
  EvdWebSelector *self = EVD_WEB_SELECTOR (obj);

  if (self->priv->default_service != NULL)
    {
      g_object_unref (self->priv->default_service);
      self->priv->default_service = NULL;
    }

  g_list_free_full (self->priv->candidates, evd_web_selector_free_candidate);
  self->priv->candidates = NULL;

  G_OBJECT_CLASS (evd_web_selector_parent_class)->dispose (obj);
}
