bd_kludge_insert(struct term *t)
{
  struct term_ptr *tp;

  if (Flags[INDEX_FOR_BACK_DEMOD].val)
    fpa_insert(t, Parms[FPA_TERMS].val, Fpa_back_demod);
  else {

    tp = get_term_ptr();
    tp->term = t;

    tp->next = Bd_kludge;
    Bd_kludge = tp;
  }
}
