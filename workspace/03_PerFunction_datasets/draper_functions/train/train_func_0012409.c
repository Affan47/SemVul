avatar_chooser_dispose (GObject *object)
{
  TpawAvatarChooser *self = (TpawAvatarChooser *) object;

  tp_clear_object (&self->priv->account);
  tp_clear_pointer (&self->priv->avatar, g_array_unref);
  tp_clear_pointer (&self->priv->mime_type, g_free);
#ifdef ENABLE_SETTINGS
  tp_clear_object (&self->priv->gsettings_ui);
#endif

  G_OBJECT_CLASS (tpaw_avatar_chooser_parent_class)->dispose (object);
}
