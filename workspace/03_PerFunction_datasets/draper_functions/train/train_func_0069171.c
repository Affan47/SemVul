func_dacs_admin(Lex_state *e, int nargs, Arglist *arglist, Expr_result *result)
{
  Arglist *x;

  x = arglist;

  if (x != NULL) {
	seterr_e(e, result, "Invalid argument to 'dacs_admin' function");
	return(-1);
  }

  result->value.token = T_INTEGER;
  result->value.val.intval = 0;
  if (e->env->credentials == NULL)
	log_msg((LOG_TRACE_LEVEL, "No credentials, no admin identity match"));
  else if (is_dacs_admin(e->env->credentials))
	result->value.val.intval = 1;

  return(0);
}
