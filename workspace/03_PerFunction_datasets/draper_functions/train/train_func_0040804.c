gnutls_pkcs7_deinit (gnutls_pkcs7_t pkcs7)
{
  if (!pkcs7)
    return;

  if (pkcs7->pkcs7)
    asn1_delete_structure (&pkcs7->pkcs7);

  gnutls_free (pkcs7);
}
