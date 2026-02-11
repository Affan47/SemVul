ssl_data_new_full(int fd, const SSL_METHOD * method, void (* callback)(struct mailstream_ssl_context * ssl_context, void * cb_data), void * cb_data)
{
  struct mailstream_ssl_data * ssl_data;
  SSL * ssl_conn;
  int r;
  SSL_CTX * tmp_ctx;
  struct mailstream_cancel * cancel;
  struct mailstream_ssl_context * ssl_context = NULL;

  mailstream_ssl_init();

  tmp_ctx = SSL_CTX_new(method);
  if (tmp_ctx == NULL)
    goto err;

  if (callback != NULL) {
    ssl_context = mailstream_ssl_context_new(tmp_ctx, fd);
    callback(ssl_context, cb_data);
  }

  SSL_CTX_set_app_data(tmp_ctx, ssl_context);
  SSL_CTX_set_client_cert_cb(tmp_ctx, mailstream_openssl_client_cert_cb);
  ssl_conn = (SSL *) SSL_new(tmp_ctx);
  if (ssl_conn == NULL)
    goto free_ctx;

  if (SSL_set_fd(ssl_conn, fd) == 0)
    goto free_ssl_conn;

again:
  r = SSL_connect(ssl_conn);

  switch(SSL_get_error(ssl_conn, r)) {
  	case SSL_ERROR_WANT_READ:
          r = wait_SSL_connect(fd, 1);
          if (r < 0)
            goto free_ssl_conn;
	  else
	    goto again;
	break;
	case SSL_ERROR_WANT_WRITE:
          r = wait_SSL_connect(fd, 0);
          if (r < 0)
            goto free_ssl_conn;
	  else
	    goto again;
	break;
  }
  if (r <= 0)
    goto free_ssl_conn;

  cancel = mailstream_cancel_new();
  if (cancel == NULL)
    goto free_ssl_conn;

  r = mailstream_prepare_fd(fd);
  if (r < 0)
    goto free_cancel;

  ssl_data = malloc(sizeof(* ssl_data));
  if (ssl_data == NULL)
    goto free_cancel;

  ssl_data->fd = fd;
  ssl_data->ssl_conn = ssl_conn;
  ssl_data->ssl_ctx = tmp_ctx;
  ssl_data->cancel = cancel;
  mailstream_ssl_context_free(ssl_context);

  return ssl_data;

 free_cancel:
  mailstream_cancel_free(cancel);
 free_ssl_conn:
  SSL_free(ssl_conn);
 free_ctx:
  SSL_CTX_free(tmp_ctx);
  mailstream_ssl_context_free(ssl_context);
 err:
  return NULL;
}
