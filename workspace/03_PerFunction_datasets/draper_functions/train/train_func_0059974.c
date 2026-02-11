replace_term(struct term *t,
				 struct term *ct,
				 struct term *vt)
{
  if (term_ident(t, ct))
    return(copy_term(vt));
  else {
    struct rel *r;
    for (r = t->farg; r; r= r->narg)
      r->argval = replace_term(r->argval, ct, vt);
    return(t);
  }
}
