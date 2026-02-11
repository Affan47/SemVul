back_demod_hints(struct clause *d)
{
  struct term *atom;
  struct term_ptr *tp, *tp2;
  struct clause_ptr *cp, *cp2;


  atom = ith_literal(d,1)->atom;

  if (Flags[INDEX_FOR_BACK_DEMOD].val)
    tp = all_instances_fpa(atom, Fpa_back_demod);
  else
    tp = all_instances(atom);

  cp = NULL;
  while (tp) {
    all_containing_hints2(tp->term, &cp);
    tp2 = tp;
    tp = tp->next;
    free_term_ptr(tp2);
  }

  while (cp) {
    struct clause *h1, *h2;
    h1 = cp->c;

    if (h1->container != Hints2)
      abend("back_demod_hints: clause not in Hints2.");


    h2 = cl_copy(h1);
    demod_cl(h2);

    if (1 || Flags[PRINT_BACK_DEMOD].val) {
      printf("    >> BACK DEMODULATING HINT %d WITH %d.\n", h1->id, d->id);


    }


    zap_ilist(h2->parents);

    h2->parents = (struct ilist *) copy_hint2_data((void *) h1->parents);


    {
      struct cl_attribute *a1;
      if ((a1 = get_attribute(h1, LABEL_ATTR))) {

	set_attribute(h2, LABEL_ATTR, "bd");
      }
    }

    if (!KEEP_BACK_DEMODULATED_HINTS) {
      rem_from_list(h1);
      index_hint2(h1, 0);
      free(h1->parents);
      h1->parents = NULL;
      cl_del_int(h1);
    }

    if (Flags[ORDER_EQ].val) {
      if (Flags[LRPO].val)
	order_equalities_lrpo(h2);
      else
	order_equalities(h2);
    }

    if (xx_tautology(h2) || hint2_subsumed(h2)) {
      free(h2->parents);
      h2->parents = NULL;
      cl_del_non(h2);
    }
    else {
      hint2_integrate(h2);
      append_cl(Hints2, h2);
      index_hint2(h2, 1);
      if (1 || Flags[PRINT_KEPT].val) {
	printf("NEW HINT: ");
	print_hint2_clause(stdout, h2);
      }
    }

    cp2 = cp;
    cp = cp->next;
    free_clause_ptr(cp2);
  }
}
