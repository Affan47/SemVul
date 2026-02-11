command_ONLY_PRINTABLE(command_t *self, worker_t *worker, char *data,
                                    apr_pool_t *ptmp) {
  char *copy;

  COMMAND_NEED_ARG("Need on|off");

  if (strcasecmp(copy, "on") == 0) {
    worker->flags |= FLAGS_ONLY_PRINTABLE;
  }
  else {
    worker->flags &= ~FLAGS_ONLY_PRINTABLE;
  }
  return APR_SUCCESS;
}
