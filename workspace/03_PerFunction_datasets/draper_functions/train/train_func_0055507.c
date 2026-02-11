g_pkcs11_slot_dispose (GObject *object)
{
  GPkcs11Slot *self = G_PKCS11_SLOT (object);
  CK_SESSION_HANDLE session = 0;

  g_mutex_lock (&self->priv->mutex);

  session = self->priv->last_session;
  self->priv->last_session = 0;

  g_mutex_unlock (&self->priv->mutex);

  if (session)
    session_close (self, session);

  G_OBJECT_CLASS (g_pkcs11_slot_parent_class)->dispose (object);
}
