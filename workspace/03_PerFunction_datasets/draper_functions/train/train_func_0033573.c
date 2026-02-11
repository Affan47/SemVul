tor_cert_get_id_digests(const tor_cert_t *cert)
{
  if (cert->pkey_digests_set)
    return &cert->pkey_digests;
  else
    return NULL;
}
