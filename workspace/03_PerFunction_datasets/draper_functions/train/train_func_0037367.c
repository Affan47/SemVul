do_if(Lex_state *e, Expr_result *result)
{
  int eval_state, is_true;

  eval_state = e->do_eval;
  while (1) {
	if ((is_true = do_if_test(e, result)) == -1)
	  return(-1);

	if (is_true)
	  e->do_eval = 0;

	if (token_matches(e, T_ELSEIF))
	  continue;
	else if (token_matches(e, T_ELSE)) {
	  if (!token_is(e, 0, T_LBRACE)) {
		seterr_s(e, result, "Opening brace is missing");
		return(-1);
	  }

	  if (e->do_eval) {
		if (do_block(e, 0, result) == -1)
		  return(-1);
	  }
	  else {
		Expr_result discard;

		if (value_init(&discard, result))
		  return(-1);
		if (do_block(e, 0, &discard) == -1)
		  return(-1);
	  }
	  break;
	}
	else {

	  if (e->do_eval)
		init_value(&result->value, T_STRING, "");
	  break;
	}
  }

  e->do_eval = eval_state;

  return(0);
}
