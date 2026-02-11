mock_interaction_new_static_certificate (GTlsCertificate *cert)
{
  MockInteraction *self;

  self = g_object_new (MOCK_TYPE_INTERACTION, NULL);

  self->static_certificate = cert ? g_object_ref (cert) : NULL;
  return G_TLS_INTERACTION (self);
}
