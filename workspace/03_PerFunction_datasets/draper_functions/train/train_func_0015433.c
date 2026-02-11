bd_kludge_delete(struct term *t)
{
  struct term_ptr *tp1, *tp2;

  if (Flags[INDEX_FOR_BACK_DEMOD].val) {
    CLOCK_START(UN_INDEX_TIME);
    fpa_delete(t, Parms[FPA_TERMS].val, Fpa_back_demod);
    CLOCK_STOP(UN_INDEX_TIME);
  }
  else
    {
      tp1 = Bd_kludge;
      tp2 = NULL;
      while (tp1 != NULL && tp1->term != t) {
	tp2 = tp1;
	tp1 = tp1->next;
      }
      if (tp1 == NULL) {
	fprintf(stderr, "WARNING, bd_kludge_delete, term not found.\n");
	printf("WARNING, bd_kludge_delete, term not found: ");
	print_term_nl(stdout, t);
      }
      else if (tp2 != NULL)
	tp2->next = tp1->next;
      else
	Bd_kludge = tp1->next;

      free_term_ptr(tp1);
    }

}
