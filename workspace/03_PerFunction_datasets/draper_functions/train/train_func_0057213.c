command_READLINE(command_t *self, worker_t *worker, char *data,
                              apr_pool_t *ptmp) {
  apr_status_t status;
  apr_size_t peeklen;
  apr_size_t len;
  sockreader_t *sockreader;
  char *buf;
  char *copy;

  COMMAND_OPTIONAL_ARG;

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

  if ((status = sockreader_read_line(sockreader, &buf)) != APR_SUCCESS) {
    goto out_err;
  }

  if (buf) {
    len = strlen(buf);
    if ((status = worker_handle_buf(worker, ptmp, buf, len))
	!= APR_SUCCESS) {
      goto out_err;
    }
  }

out_err:
  if (strcasecmp(copy, "DO_NOT_CHECK") != 0) {
    status = worker_assert(worker, status);
  }

  return status;
}
