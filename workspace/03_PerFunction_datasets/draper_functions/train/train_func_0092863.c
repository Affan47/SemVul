cmd_prev_candidate(struct anthy_input_context* ictx)
{
  struct a_segment* as;

  ictx->enum_cand_count++;

  as = ictx->cur_segment;

  if (ictx->enum_reverse)
    as->cand = ictx->last_gotten_cand;
  else
    ictx->enum_reverse = 1;

  if (as->cand == NTH_UNCONVERTED_CANDIDATE) {
    while (as) {
      if (as->cand == NTH_UNCONVERTED_CANDIDATE) {
	as->cand = 0;
      }
      as = as->next;
    }
    ictx->last_gotten_cand = 0;
  } else {
    if (--as->cand < 0)
      as->cand = as->ass.nr_candidate - 1;
    ictx->last_gotten_cand = as->cand;
  }
}
