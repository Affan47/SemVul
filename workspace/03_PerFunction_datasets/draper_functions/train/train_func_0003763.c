acs_expr_string(char *expr, Acs_expr_ns_arg *ns_args, char **result_str)
{
  int i;
  Acs_environment env;
  Acs_expr_result st;

  acs_new_env(&env);
  env.redirect_reason = ACS_DENIAL_REASON_BY_REDIRECT;

  for (i = 0; ns_args[i].name != NULL; i++)
	var_ns_new(&env.namespaces, ns_args[i].name, ns_args[i].kwv);

  st = acs_expr_string_env(expr, &env, result_str);

  return(st);
}
