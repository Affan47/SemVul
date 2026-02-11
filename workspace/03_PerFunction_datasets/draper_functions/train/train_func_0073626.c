tls_error(SSL *ssl, int r, int flags)
{
        int err = SSL_get_error(ssl,r);
        switch (err) {
          case SSL_ERROR_NONE:
                  return NO_ERROR;
          case SSL_ERROR_ZERO_RETURN:
                  if (flags & IGNORE_ZERO_RETURN)
                          return ZERO_RETURN;
                  mm_SSL_ERR(0);
                  return ZERO_RETURN;
          case SSL_ERROR_WANT_READ:
                  PyErr_SetNone(mm_TLSWantRead);
                  return ERROR;
          case SSL_ERROR_WANT_WRITE:
                  PyErr_SetNone(mm_TLSWantWrite);
                  return ERROR;
          case SSL_ERROR_SYSCALL:
                  if (flags & IGNORE_SYSCALL)
                          return NO_ERROR;
                  PyErr_SetNone(mm_TLSClosed);
                  return ERROR;
          default:
                  mm_SSL_ERR(0);
                  return ERROR;
        }
}
