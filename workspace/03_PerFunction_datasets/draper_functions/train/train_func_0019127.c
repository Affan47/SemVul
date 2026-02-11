set_wt_term(struct term *t)
{
  struct rel *r;
  int n;

  if (t->type == COMPLEX) {

    if (is_symbol(t, "$", 1) && t->farg->argval->type == NAME &&
	str_int(sn_to_str(t->farg->argval->sym_num), &n)) {


      SET_BIT(t->bits, SCRATCH_BIT);
      t->fpa_id = n;
    }
    else {
      for (r = t->farg; r; r = r->narg)
	set_wt_term(r->argval);
    }
  }

}
