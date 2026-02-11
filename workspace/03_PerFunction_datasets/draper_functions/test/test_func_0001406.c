command_UNSET(command_t * self, worker_t * worker,
                           char *data, apr_pool_t *ptmp) {
  const char *var;
  char *copy;
  int i;

  COMMAND_NEED_ARG("Variable and value not specified");

  var = copy;
  for (i = 0; var[i] != 0 && strchr(VAR_ALLOWED_CHARS, var[i]); i++);
  if (var[i] != 0) {
    worker_log(worker, LOG_ERR, "Char '%c' is not allowed in \"%s\"", var[i], var);
    return APR_EINVAL;
  }

  if (store_get(worker->locals, var)) {
    store_unset(worker->locals, var);
  }
  else {
    store_unset(worker->vars, var);
  }

  return APR_SUCCESS;
}
