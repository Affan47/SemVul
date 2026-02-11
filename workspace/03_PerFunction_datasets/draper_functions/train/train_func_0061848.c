compute_best_break (a_paragraph *p, unsigned int wn, a_word *res,
		    unsigned int widx)
{
  unsigned int nwords = p->nwords;
  const a_word *w = p->words;
  unsigned int spaces = 0;
  a_width width = 0;

  a_cost best_cost = MAX_COST;
  const a_word *best_break = 0;


  while (wn < nwords) {
    a_cost cost;


    width += w[wn].width;


    if ((width + spaces * p->min_space_width) > p->max_widths[widx])
      break;


    cost = compute_break_cost (p, wn, width, spaces, widx);
    if (cost < best_cost) {
      best_cost = cost;
      best_break = w + wn;
    }


    spaces += w[wn].spaces;
    ++wn;
  }


  if (res) {
    res->next_break[widx] = best_break;
    res->next_break_cost[widx] = (wn >= nwords) ? 0 : best_cost;
  }
  return best_break;
}
