math_parse_factor(math_eval_t *hook) {
  apr_status_t status;
  int token;
  long *number;
  long sign = 1;

  token = math_peek_token(hook);
  switch (token) {
  case MATH_ADD:

    math_get_token(hook);
  case MATH_SUB:

    sign = -1;
    math_get_token(hook);
  case MATH_NUM:
    number = apr_pcalloc(hook->pool, sizeof(*number));
    *number = hook->last_number * sign;
    SKM_sk_push(long, hook->stack, number);
    math_get_token(hook);
    return APR_SUCCESS;
    break;
  case MATH_PARENT_L:
    token = math_get_token(hook);
    status = math_parse_expression(hook);
    token = math_peek_token(hook);
    if (token != MATH_PARENT_R) {
      return APR_EINVAL;
    }
    token = math_get_token(hook);
    return status;
    break;
  default:
    return APR_EINVAL;
    break;
  }
}
