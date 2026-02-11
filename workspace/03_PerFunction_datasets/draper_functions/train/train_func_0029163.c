evd_tls_session_copy_properties (EvdTlsSession *self,
                                 EvdTlsSession *target)
{
  g_return_if_fail (EVD_IS_TLS_SESSION (self));
  g_return_if_fail (self != target);

  g_object_set (target,
                "credentials", evd_tls_session_get_credentials (self),
                "priority", self->priv->priority,
                "require-peer-cert", self->priv->require_peer_cert,
                NULL);
}
