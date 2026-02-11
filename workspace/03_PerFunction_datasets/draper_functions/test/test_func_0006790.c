heir10b(Lex_state *e, Expr_result *result)
{
  Expr_result res1;

  if (value_init(&res1, result))
	return(-1);

  if (heir11(e, result) == -1)
	return(-1);

  while (1) {
	if (token_matches(e, T_DOT)) {
	  if (heir11(e, &res1) == -1) {
		seterr_s(e, result, "Invalid operand");
		return(-1);
	  }

	  if (eval2(e, result, T_DOT, result, &res1) == -1)
		return(-1);
	  log_msg((LOG_TRACE_LEVEL, "dot"));
	}
	else
	  break;
  }

  return(0);
}
