block_BINARY_SEND(worker_t * worker, worker_t *parent, apr_pool_t *ptmp) {
  apr_status_t status = APR_SUCCESS;
  char *copy;
  apr_size_t i;

  if (!worker->socket || !worker->socket->socket) {
    return APR_ENOSOCKET;
  }

  for (i = 1; i < store_get_size(worker->params); i++) {
    int unresolved;

    copy = store_get_copy(worker->params, worker->pcache, apr_itoa(ptmp, i));
    copy = worker_replace_vars(worker, copy, &unresolved, ptmp);

    if (unresolved) {
      apr_table_addn(worker->cache,
		     apr_pstrdup(worker->pcache, "BINARY;resolve"), copy);
    }
    else {
      apr_table_addn(worker->cache,
		     apr_pstrdup(worker->pcache, "BINARY"), copy);
    }
  }

  return status;
}
