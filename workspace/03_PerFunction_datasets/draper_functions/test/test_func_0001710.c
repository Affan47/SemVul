dolmove_hyptrav(node *r)
{

  if (!r->tip)
    dolmove_correct(r);
  if (((1L << dispbit) & r->stateone[dispword - 1]) != 0) {
    if (((1L << dispbit) & r->statezero[dispword - 1]) != 0) {
      if (dollo)
        r->state = '?';
      else
        r->state = 'P';
    } else
      r->state = '1';
  } else {
    if (((1L << dispbit) & r->statezero[dispword - 1]) != 0)
      r->state = '0';
    else
      r->state = '?';
  }
  if (!r->tip) {
    dolmove_hyptrav(r->next->back);
    dolmove_hyptrav(r->next->next->back);
  }
}
