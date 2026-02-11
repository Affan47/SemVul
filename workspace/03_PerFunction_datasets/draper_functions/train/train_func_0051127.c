tpl_text_channel_dispose (GObject *obj)
{
  TplTextChannelPriv *priv = TPL_TEXT_CHANNEL (obj)->priv;

  tp_clear_object (&priv->remote);
  tp_clear_object (&priv->self);

  G_OBJECT_CLASS (_tpl_text_channel_parent_class)->dispose (obj);
}
