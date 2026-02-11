imd_delete(struct clause *demod,
		struct imd_tree *root_imd)
{
  struct imd_tree *end, *i2, *i3, *parent;
  struct term_ptr *tp1, *tp2;
  struct term_ptr *imdp, *path;
  struct term *atom, *alpha;


  path = NULL;
  atom = ith_literal(demod,1)->atom;

  if (atom->varnum == CONDITIONAL_DEMOD)
    alpha = atom->farg->narg->argval->farg->argval;
  else
    alpha = atom->farg->argval;

  end = end_term_imd(alpha, root_imd, &path);

  if (end == NULL) {
    print_term_nl(stdout, alpha);
    abend("imd_delete, can't find alpha.");
  }

  tp1 = end->atoms;
  tp2 = NULL;
  while (tp1 != NULL && tp1->term != atom) {
    tp2 = tp1;
    tp1 = tp1->next;
  }

  if (tp1 == NULL) {
    print_term_nl(stdout, atom);
    abend("imd_delete, can't find atom.");
  }

  if (tp2 == NULL)
    end->atoms = tp1->next;
  else
    tp2->next = tp1->next;
  free_term_ptr(tp1);

  if (end->atoms == NULL) {

    imdp = path;
    while (end->kids == NULL && end != root_imd) {
      parent = (struct imd_tree *) imdp->term;
      imdp = imdp->next;
      i2 = parent->kids;
      i3 = NULL;
      while (i2 != end) {
	i3 = i2;
	i2 = i2->next;
      }
      if (i3 == NULL)
	parent->kids = i2->next;
      else
	i3->next = i2->next;
      free_imd_tree(i2);
      end = parent;
    }
  }


  while (path != NULL) {
    imdp = path;
    path = path->next;
    free_term_ptr(imdp);
  }

}
