matchesCertificate(SiCertificate& cert)
{
  X509 *x509 = cert.getRawCertificate();
  if ((x509 == NULL)||(pkey == NULL)) return OFFalse;
  if (X509_check_private_key(x509, pkey)) return OFTrue;
  return OFFalse;
}
