better_edge_p (basic_block bb, edge e, int prob, int freq, int best_prob,
	       int best_freq)
{
  bool is_better_edge;


  int diff_prob = best_prob / 10;
  int diff_freq = best_freq / 10;

  if (prob > best_prob + diff_prob)

    is_better_edge = true;
  else if (prob < best_prob - diff_prob)

    is_better_edge = false;
  else if (freq < best_freq - diff_freq)


    is_better_edge = true;
  else if (freq > best_freq + diff_freq)

    is_better_edge = false;
  else if (e->dest->prev_bb == bb)


    is_better_edge = true;
  else
    is_better_edge = false;

  return is_better_edge;
}
