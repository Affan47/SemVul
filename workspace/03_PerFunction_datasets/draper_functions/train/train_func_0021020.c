command_UP(command_t *self, worker_t *worker, char *data,
                        apr_pool_t *ptmp) {
  char *copy;

  apr_int32_t backlog = LISTENBACKLOG_DEFAULT;

  COMMAND_OPTIONAL_ARG;

  if (copy[0] != '\0') {
    backlog = apr_atoi64(copy);
  }

  return worker_listener_up(worker, backlog);
}
