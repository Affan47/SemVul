connect_better_edge_p (const_edge e, bool src_index_p, int best_len,
		       const_edge cur_best_edge, struct trace *traces)
{
  int e_index;
  int b_index;
  bool is_better_edge;

  if (!cur_best_edge)
    return true;

  if (optimize_function_for_size_p (cfun))
    {
      e_index = src_index_p ? e->src->index : e->dest->index;
      b_index = src_index_p ? cur_best_edge->src->index
			      : cur_best_edge->dest->index;

      return b_index > e_index;
    }

  if (src_index_p)
    {
      e_index = e->src->index;

      if (e->probability > cur_best_edge->probability)

	is_better_edge = true;
      else if (e->probability < cur_best_edge->probability)

	is_better_edge = false;
      else if (traces[bbd[e_index].end_of_trace].length > best_len)


	is_better_edge = true;
      else
	is_better_edge = false;
    }
  else
    {
      e_index = e->dest->index;

      if (e->probability > cur_best_edge->probability)

	is_better_edge = true;
      else if (e->probability < cur_best_edge->probability)

	is_better_edge = false;
      else if (traces[bbd[e_index].start_of_trace].length > best_len)


	is_better_edge = true;
      else
	is_better_edge = false;
    }

  return is_better_edge;
}
