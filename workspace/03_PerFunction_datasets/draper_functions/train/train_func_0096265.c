func_list(Lex_state *e, int nargs, Arglist *arglist, Expr_result *result)
{
  Arglist *x;
  Value v;

  init_value(&v, T_LIST, sizeof(Value));

  x = arglist;
  while (x != NULL) {
	dsvec_add_ptr(v.val.listval.list, &x->result->value);
	x = x->next;
  }

  result->value.token = T_LIST;
  result->value = v;

  return(0);
}
