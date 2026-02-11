g_pkcs11_pin_set_value (GTlsPassword  *password,
                        guchar        *value,
                        gssize         length,
                        GDestroyNotify destroy)
{
  GPkcs11Pin *self = G_PKCS11_PIN (password);

  if (self->priv->pin)
    {
      p11_kit_pin_unref (self->priv->pin);
      self->priv->pin = NULL;
    }

  if (length < 0)
    length = strlen ((gchar *) value);

  self->priv->pin = p11_kit_pin_new_for_buffer (value, length, destroy);
}
