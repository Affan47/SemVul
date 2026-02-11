block_BINARY_RECV(worker_t * worker, worker_t *parent, apr_pool_t *ptmp) {
  apr_pool_t *pool;
  apr_status_t status;
  apr_size_t recv_len;
  apr_size_t peeklen;
  sockreader_t *sockreader;
  char *buf;
  const char *val;

  int poll = 0;

  val = store_get(worker->params, "1");

  recv_len = apr_atoi64(val);

  apr_pool_create(&pool, NULL);

  if (worker->socket->sockreader == NULL) {
    peeklen = worker->socket->peeklen;
    worker->socket->peeklen = 0;
    if ((status = sockreader_new(&worker->socket->sockreader,
                                 worker->socket->transport,
				 worker->socket->peek, peeklen))
        != APR_SUCCESS) {
      goto out_err;
    }
  }
  sockreader = worker->socket->sockreader;

  if ((status = content_length_reader(sockreader, &buf, &recv_len, "")) != APR_SUCCESS) {
    if (poll && APR_STATUS_IS_INCOMPLETE(status)) {
      status = APR_SUCCESS;
    }
    else {
      goto out_err;
    }
  }

  worker->flags |= FLAGS_PRINT_HEX;
  if ((status = worker_handle_buf(worker, pool, buf, recv_len))
      != APR_SUCCESS) {
    goto out_err;
  }

out_err:
  status = worker_assert(worker, status);
  apr_pool_destroy(pool);

  return status;
}
