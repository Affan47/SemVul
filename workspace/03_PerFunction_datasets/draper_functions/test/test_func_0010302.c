X509_get_issuer_name (const X509 * cert)
{
  gnutls_x509_dn *dn;
  dn = (gnutls_x509_dn *) calloc (1, sizeof (gnutls_x509_dn));
  if (gnutls_x509_extract_certificate_issuer_dn (cert, dn) < 0)
    {
      free (dn);
      return NULL;
    }
  return dn;
}
