ssl_accept(SSL *ssl, char **error, apr_pool_t *pool) {
  int rc;
  int err;

  *error = NULL;


  if (!ssl) {
    *error = apr_pstrdup(pool, "No ssl context");
    return APR_EINVAL;
  }

tryagain:
  apr_sleep(1);
  if (SSL_is_init_finished(ssl)) {
    return APR_SUCCESS;
  }

  if ((rc = SSL_accept(ssl)) <= 0) {
    err = SSL_get_error(ssl, rc);

    if (err == SSL_ERROR_ZERO_RETURN) {
      *error = apr_pstrdup(pool, "SSL accept connection closed");
      return APR_ECONNABORTED;
    }
    else if (err == SSL_ERROR_WANT_READ) {
      *error = apr_pstrdup(pool, "SSL accept SSL_ERROR_WANT_READ.");
      goto tryagain;
    }
    else if (ERR_GET_LIB(ERR_peek_error()) == ERR_LIB_SSL &&
	     ERR_GET_REASON(ERR_peek_error()) == SSL_R_HTTP_REQUEST) {


      *error = apr_pstrdup(pool, "SSL accept client speaks plain HTTP");
      return APR_ENOTSOCK;
    }
    else if (err == SSL_ERROR_SYSCALL) {
       *error = apr_pstrdup(pool,
                  "SSL accept interrupted by system "
                  "[Hint: Stop button pressed in browser?!]");
       return APR_ECONNABORTED;
    }
    else  {


      *error = apr_psprintf(pool, "SSL library error %d in accept", err);
      return APR_ECONNABORTED;
    }
  }

  return APR_SUCCESS;
}
