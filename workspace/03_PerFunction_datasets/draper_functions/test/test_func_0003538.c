math_parse_expression(math_eval_t *hook) {
  int token;
  apr_status_t status;
  long *right;
  long *left;
  long *result;

  if ((status = math_parse_term(hook)) != APR_SUCCESS) {
    return status;
  }

  token = math_peek_token(hook);
  while (token != MATH_EOF) {
    if (token == MATH_ADD || token == MATH_SUB) {
      math_get_token(hook);
    }
    else {
      return APR_SUCCESS;
    }

    if ((status = math_parse_term(hook)) != APR_SUCCESS) {
      return status;
    }

    right = SKM_sk_pop(long, hook->stack);
    left = SKM_sk_pop(long, hook->stack);
    result = apr_pcalloc(hook->pool, sizeof(*result));
    switch (token) {
    case MATH_ADD:
      *result = *left + *right;
      break;
    case MATH_SUB:
      *result = *left - *right;
      break;
    default:
      break;
    }
    SKM_sk_push(long, hook->stack, result);

    token = math_peek_token(hook);
  }
  return APR_SUCCESS;
}
