tor_tls_debug_state_callback(const SSL *ssl, int type, int val)
{
  log_debug(LD_HANDSHAKE, "SSL %p is now in state %s [type=%d,val=%d].",
            ssl, SSL_state_string_long(ssl), type, val);
}
