eval_function(char *name, Lex_state *e, Arglist *args, Expr_result *result)
{
  int nargs, st;
  Func_info *fi;

  if ((fi = lookup_function(name)) == NULL) {
	seterr_e(e, result,
			 ds_xprintf("Unrecognized function name: \"%s\"", name));
	return(-1);
  }

  if ((nargs = validate_func_call(e, fi, args)) == -1) {
	seterr_e(e, result, ds_xprintf("Invalid function call: \"%s\"", name));
	return(-1);
  }

  result->err = ACS_EXPR_FALSE;
  result->errmsg = NULL;

  if (!e->do_eval)
	return(0);


  st = fi->func(e, nargs, args, result);
  if (st == -1)
	return(-1);

  return(0);
}
