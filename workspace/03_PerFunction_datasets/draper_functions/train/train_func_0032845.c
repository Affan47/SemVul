networkstatus_check_document_signature(const networkstatus_t *consensus,
                                       document_signature_t *sig,
                                       const authority_cert_t *cert)
{
  char key_digest[DIGEST_LEN];
  const int dlen = sig->alg == DIGEST_SHA1 ? DIGEST_LEN : DIGEST256_LEN;
  char *signed_digest;
  size_t signed_digest_len;

  if (crypto_pk_get_digest(cert->signing_key, key_digest)<0)
    return -1;
  if (tor_memneq(sig->signing_key_digest, key_digest, DIGEST_LEN) ||
      tor_memneq(sig->identity_digest, cert->cache_info.identity_digest,
                 DIGEST_LEN))
    return -1;

  signed_digest_len = crypto_pk_keysize(cert->signing_key);
  signed_digest = tor_malloc(signed_digest_len);
  if (crypto_pk_public_checksig(cert->signing_key,
                                signed_digest,
                                signed_digest_len,
                                sig->signature,
                                sig->signature_len) < dlen ||
      tor_memneq(signed_digest, consensus->digests.d[sig->alg], dlen)) {
    log_warn(LD_DIR, "Got a bad signature on a networkstatus vote");
    sig->bad_signature = 1;
  } else {
    sig->good_signature = 1;
  }
  tor_free(signed_digest);
  return 0;
}
