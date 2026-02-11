new_demod(struct clause *c,
			 int demod_flag)
{
  struct clause *d;
  struct ilist *ip0, *ip1;

  Stats[NEW_DEMODS]++;
  d = cl_copy(c);
  ip0 = get_ilist(); ip0->i = NEW_DEMOD_RULE;
  ip1 = get_ilist(); ip1->i = c->id;
  d->parents = ip0; ip0->next = ip1;
  cl_integrate(d);
  if (demod_flag == 2)
    ith_literal(d,1)->atom->varnum = LEX_DEP_DEMOD;
  if (Flags[BACK_DEMOD].val) {
    struct term *atom;
    atom = ith_literal(c,1)->atom;
    SET_BIT(atom->bits, SCRATCH_BIT);
  }
  if (Flags[DEMOD_LINEAR].val == 0) {
    if (Demod_imd == NULL)
      Demod_imd = get_imd_tree();
    imd_insert(d, Demod_imd);
  }

  append_cl(Demodulators, d);
  return(d);

}
