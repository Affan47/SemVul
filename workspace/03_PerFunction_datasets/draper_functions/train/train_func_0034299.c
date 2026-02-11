block_TCP_CONNECT(worker_t * worker, worker_t *parent, apr_pool_t *ptmp) {
  apr_status_t status;
  char *portname;
  char *hostname;

  if ((status = worker_flush(worker, ptmp)) != APR_SUCCESS) {
    return status;
  }

  if ((status = worker_test_unused(worker)) != APR_SUCCESS) {
    return status;
  }

  hostname = store_get_copy(worker->params, ptmp, "1");
  portname = store_get_copy(worker->params, ptmp, "2");

  worker_log(worker, LOG_DEBUG, "get socket \"%s:%s\"", hostname, portname);
  worker_get_socket(worker, hostname, portname);

  if (worker->socket->socket_state == SOCKET_CLOSED) {
    status = tcp_connect(worker, hostname, portname);

    if ((status = tcp_hook_connect(worker)) != APR_SUCCESS) {
      return status;
    }

    worker->socket->socket_state = SOCKET_CONNECTED;
  }

  worker_test_reset(worker);

  return status;
}
