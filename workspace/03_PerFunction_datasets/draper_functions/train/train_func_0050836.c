introduce_var_term(struct term *t,
			       struct term *v,
			       int vnum)
{
  struct rel *r;

  switch (t->type) {
  case NAME:
    if (term_ident(t,v)) {
      t->type = VARIABLE;
      t->varnum = vnum;
      t->sym_num = 0;
    }
    break;
  case VARIABLE:
    break;
  case COMPLEX:
    for (r = t->farg; r; r = r->narg)
      introduce_var_term(r->argval, v, vnum);
    break;
  }

}
