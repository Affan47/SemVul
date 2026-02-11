gnutls_x509_crq_get_dn_by_oid (gnutls_x509_crq_t crq, const char *oid,
                               int indx, unsigned int raw_flag,
                               void *buf, size_t * sizeof_buf)
{
  if (crq == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  return _gnutls_x509_parse_dn_oid
    (crq->crq,
     "certificationRequestInfo.subject.rdnSequence",
     oid, indx, raw_flag, buf, sizeof_buf);
}
