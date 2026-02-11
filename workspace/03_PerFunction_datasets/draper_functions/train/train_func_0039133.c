sos_keep2(Topform c, Clist sos, Prover_options opt)
{
  int keep_factor = parm(opt->sos_keep_factor);
  int sos_size = clist_length(sos);
  int sos_limit = (parm(opt->sos_limit)== -1 ? INT_MAX : parm(opt->sos_limit));
  BOOL keep;
  if (sos_size < sos_limit / keep_factor)
    keep = TRUE;
  else {
    int iters;
    c->id = INT_MAX;
    iters = least_iters_to_selection(c, &Low, NULL);
    if (Debug)
      printf("iters=%d, wt=%.3f\n", iters, c->weight);
    if (iters < sos_limit / keep_factor)
      keep = TRUE;
    else {
      if (c->weight < Low_water_keep) {
	Low_water_keep = c->weight;
	printf("\nLow Water (keep): wt=%.3f, iters=%d\n", c->weight, iters);
	if (stringparm(opt->stats, "all"))
	  selector_report();
	fflush(stdout);
      }
      Sos_deleted++;
      keep = FALSE;
    }
    c->id = 0;
  }
  return keep;
}
