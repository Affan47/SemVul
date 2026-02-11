tor_tls_verify(int severity, tor_tls_t *tls, crypto_pk_t **identity_key)
{
  X509 *cert = NULL, *id_cert = NULL;
  EVP_PKEY *id_pkey = NULL;
  RSA *rsa;
  int r = -1;

  *identity_key = NULL;

  try_to_extract_certs_from_tls(severity, tls, &cert, &id_cert);
  if (!cert)
    goto done;
  if (!id_cert) {
    log_fn(severity,LD_PROTOCOL,"No distinct identity certificate found");
    goto done;
  }
  tls_log_errors(tls, severity, LD_HANDSHAKE, "before verifying certificate");

  if (!(id_pkey = X509_get_pubkey(id_cert)) ||
      X509_verify(cert, id_pkey) <= 0) {
    log_fn(severity,LD_PROTOCOL,"X509_verify on cert and pkey returned <= 0");
    tls_log_errors(tls, severity, LD_HANDSHAKE, "verifying certificate");
    goto done;
  }

  rsa = EVP_PKEY_get1_RSA(id_pkey);
  if (!rsa)
    goto done;
  *identity_key = _crypto_new_pk_from_rsa(rsa);

  r = 0;

 done:
  if (cert)
    X509_free(cert);
  if (id_pkey)
    EVP_PKEY_free(id_pkey);


  tls_log_errors(tls, LOG_WARN, LD_HANDSHAKE, "finishing tor_tls_verify");

  return r;
}
