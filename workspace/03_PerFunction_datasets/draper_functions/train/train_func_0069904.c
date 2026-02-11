block_CODER_URLDEC(worker_t *worker, worker_t *parent, apr_pool_t *ptmp) {

  const char *string;
  const char *var;
  char c;
  int i;
  int j;
  apr_size_t len;
  char *inplace;

  string = store_get(worker->params, "1");
  var = store_get(worker->params, "2");

  if (!string) {
    worker_log(worker, LOG_ERR, "Nothing to decode");
    return APR_EGENERAL;
  }
  if (!var) {
    worker_log(worker, LOG_ERR, "Variable not specified");
    return APR_EGENERAL;
  }

  inplace = apr_pstrdup(ptmp, string);
  len = strlen(string);
  for (i = 0, j = 0; i < len; i++, j++) {
    c = string[i];
    if (string[i] == '+') {
      c = 32;
    }
    else if (string[i] == '%') {
      if (i + 2 < len) {
        c = x2c(&string[i + 1]);
        i += 2;
      }
    }
    else if (string[i] == '\\' && i + 1 < len && string[i + 1] == 'x') {
      if (i + 3 < len) {
        c = x2c(&string[i + 2]);
        i += 3;
      }
    }
    inplace[j] = c;
  }
  inplace[j] = 0;

  worker_var_set(parent, var, inplace);

  return APR_SUCCESS;
}
