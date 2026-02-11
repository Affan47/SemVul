block_MATH_OP(worker_t *worker, worker_t *parent,
                                  apr_pool_t *ptmp) {
  const char *param;
  const char *op;
  apr_int64_t ileft;
  apr_int64_t iright;
  apr_int64_t result;

  param = store_get(worker->params, "1");
  if (param == NULL) {
    worker_log(worker, LOG_ERR, "<left> value expected");
    return APR_EINVAL;
  }
  ileft = apr_atoi64(param);

  op = store_get(worker->params, "2");
  if (op == NULL) {
    worker_log(worker, LOG_ERR, "ADD, SUB, MUL or DIV expected");
    return APR_EINVAL;
  }

  param = store_get(worker->params, "3");
  if (param == NULL) {
    worker_log(worker, LOG_ERR, "<right> value expected");
    return APR_EINVAL;
  }
  iright = apr_atoi64(param);

  param = store_get(worker->params, "4");
  if (param == NULL) {
    worker_log(worker, LOG_ERR, "<var> expected");
    return APR_EINVAL;
  }


  if (strcasecmp(op, "ADD") == 0) {
    result = ileft + iright;
  }
  else if (strcasecmp(op, "SUB") == 0) {
    result = ileft - iright;
  }
  else if (strcasecmp(op, "MUL") == 0) {
    result = ileft * iright;
  }
  else if (strcasecmp(op, "DIV") == 0) {
    if (iright == 0) {
      worker_log(worker, LOG_ERR, "Division by zero");
      return APR_EINVAL;
    }
    result = ileft / iright;
  }
  else {
    worker_log(worker, LOG_ERR, "Unknown operant %s", op);
    return APR_ENOTIMPL;
  }


  worker_var_set(parent, param, apr_off_t_toa(ptmp, result));

  return APR_SUCCESS;
}
