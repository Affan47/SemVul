random_op_term(int depth)
{
  static int initialized = 0;
  static int symnum[13];

  if (!initialized) {
    symnum[0] = str_to_sn("a", 0);
    symnum[1] = str_to_sn("->", 2);
    symnum[2] = str_to_sn("|", 2);
    symnum[3] = str_to_sn("&", 2);
    symnum[4] = str_to_sn("~", 1);
    symnum[5] = str_to_sn("=", 2);
    symnum[6] = str_to_sn("+", 2);
    symnum[7] = str_to_sn("*", 2);
    symnum[8] = str_to_sn("\'", 1);
    symnum[9] = str_to_sn("$cons", 2);
    symnum[10] = str_to_sn("$nil", 0);
    symnum[11] = str_to_sn("$quantified", 1);
    symnum[12] = str_to_sn("f", 2);
    initialized = 1;
  }

  if (depth == 0)
    return get_rigid_term("b", 0);
  else {
    Term t;
    int arity, i, sn;

    sn = symnum[rand() % 13];
    arity = sn_to_arity(sn);

    if (is_symbol(sn, "$quantified", 1)) {
      Term q = get_rigid_term("$quantified", 1);

      Term a = get_rigid_term("all", 0);
      Term x = get_rigid_term("x", 0);
      Term r = random_op_term(depth-1);

      Term t = get_nil_term();

      t = listterm_cons(r, t);
      t = listterm_cons(x, t);
      t = listterm_cons(a, t);

      ARG(q,0) = t;
      return q;
    }
    else {

      t = get_rigid_term(sn_to_str(sn), arity);
      for (i = 0; i < arity; i++)
	ARG(t,i) = random_op_term(depth-1);
      return t;
    }
  }
}
