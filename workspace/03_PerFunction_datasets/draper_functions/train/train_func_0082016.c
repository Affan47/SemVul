sn_occur(int sn,
	     struct term *t)
{
  struct rel *r;
  int occurs;

  if (t->type != COMPLEX)
    return(t->sym_num == sn);
  else if (t->sym_num == sn)
    return(1);
  else {
    occurs = 0;
    r = t->farg;
    while (r && occurs == 0) {
      occurs = sn_occur(sn, r->argval);
      r = r->narg;
    }
    return(occurs);
  }
}
