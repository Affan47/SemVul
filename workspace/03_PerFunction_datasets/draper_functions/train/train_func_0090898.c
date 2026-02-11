tor_tls_assert_renegotiation_unblocked(tor_tls_t *tls)
{
  if (use_unsafe_renegotiation_flag) {
    tor_assert(0 != (tls->ssl->s3->flags &
                     SSL3_FLAGS_ALLOW_UNSAFE_LEGACY_RENEGOTIATION));
  }
  if (use_unsafe_renegotiation_op) {
    long options = SSL_get_options(tls->ssl);
    tor_assert(0 != (options & SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION));
  }
}
