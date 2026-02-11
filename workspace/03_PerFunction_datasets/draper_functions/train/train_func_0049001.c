tpl_entity_finalize (GObject *obj)
{
  TplEntity *self = TPL_ENTITY (obj);
  TplEntityPriv *priv = self->priv;

  tp_clear_pointer (&priv->alias, g_free);
  tp_clear_pointer (&priv->identifier, g_free);
  tp_clear_pointer (&priv->avatar_token, g_free);

  G_OBJECT_CLASS (tpl_entity_parent_class)->finalize (obj);
}
