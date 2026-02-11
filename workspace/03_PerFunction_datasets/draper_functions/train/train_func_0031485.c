goa_kerberos_identity_inquiry_dispose (GObject *object)
{
  GoaKerberosIdentityInquiry *self = GOA_KERBEROS_IDENTITY_INQUIRY (object);

  g_clear_object (&self->priv->identity);
  g_clear_pointer (&self->priv->name, (GDestroyNotify) g_free);
  g_clear_pointer (&self->priv->banner, (GDestroyNotify) g_free);

  g_list_foreach (self->priv->queries,
                  (GFunc) goa_kerberos_identity_query_free, NULL);
  g_clear_pointer (&self->priv->queries, (GDestroyNotify) g_list_free);
}
