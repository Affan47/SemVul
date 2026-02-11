dfs_enumerate_from (bb, reverse, predicate, rslt, rslt_max, data)
     basic_block bb;
     int reverse;
     bool (*predicate) PARAMS ((basic_block, void *));
     basic_block *rslt;
     int rslt_max;
     void *data;
{
  basic_block *st, lbb;
  int sp = 0, tv = 0;

  st = xcalloc (rslt_max, sizeof (basic_block));
  rslt[tv++] = st[sp++] = bb;
  bb->flags |= BB_VISITED;
  while (sp)
    {
      edge e;
      lbb = st[--sp];
      if (reverse)
        {
          for (e = lbb->pred; e; e = e->pred_next)
	    if (!(e->src->flags & BB_VISITED) && predicate (e->src, data))
	      {
	        if (tv == rslt_max)
	          abort ();
	        rslt[tv++] = st[sp++] = e->src;
	        e->src->flags |= BB_VISITED;
	      }
        }
      else
        {
          for (e = lbb->succ; e; e = e->succ_next)
	    if (!(e->dest->flags & BB_VISITED) && predicate (e->dest, data))
	      {
	        if (tv == rslt_max)
	          abort ();
	        rslt[tv++] = st[sp++] = e->dest;
	        e->dest->flags |= BB_VISITED;
	      }
	}
    }
  free (st);
  for (sp = 0; sp < tv; sp++)
    rslt[sp]->flags &= ~BB_VISITED;
  return tv;
}
