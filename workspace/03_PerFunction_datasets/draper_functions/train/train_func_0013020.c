func_typeof(Lex_state *e, int nargs, Arglist *arglist, Expr_result *result)
{
  char *s1;
  Arglist *x;

  x = arglist;
  if (x->next != NULL) {
	Token t;

	if (!str_or_lit(x->result->value.token)) {
	  seterr_e(e, result, "Invalid argument to 'typeof' function");
	  return(-1);
	}
	s1 = x->result->value.val.strval;

	x = x->next;
	if (x->next != NULL) {
	  seterr_e(e, result, "Invalid argument to 'typeof' function");
	  return(-1);
	}

	if ((t = typename_to_type(s1)) == T_UNDEF) {
	  seterr_e(e, result, "Invalid argument to 'typeof' function");
	  return(-1);
	}
	result->value.token = T_INTEGER;
	result->value.val.intval = (x->result->value.token == t);
  }
  else {
	result->value.token = T_STRING;
	result->value.val.strval = type_to_typename(x->result->value.token);
  }

  return(0);
}
