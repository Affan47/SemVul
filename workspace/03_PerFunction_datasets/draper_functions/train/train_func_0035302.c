worst_clause_of_priority_group(Select_state ss)
{
  Topform worst = NULL;
  double max = 0.0;
  Plist p;
  for (p = ss->selectors; p; p = p->next) {
    Giv_select gs = p->v;
    if (gs->idx) {
      Topform c = avl_largest(gs->idx);
      double x = iterations_to_selection(gs->part, avl_size(gs->idx),
					 current_cycle_size(ss),
					 ss->occurrences,
					 Sos_size);


      double y = least_iters_to_selection(c, ss, p);

      double least = (x < y ? x : y);

      if (least > max) {
	max = least;
	worst = c;
      }
    }
  }
  return worst;
}
