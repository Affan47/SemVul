is_edge_inconsistent (vec<edge, va_gc> *edges)
{
  edge e;
  edge_iterator ei;
  FOR_EACH_EDGE (e, ei, edges)
    {
      if (!EDGE_INFO (e)->ignore)
        {
          if (e->count < 0
	      && (!(e->flags & EDGE_FAKE)
	          || !block_ends_with_call_p (e->src)))
	    {
	      if (dump_file)
		{
		  fprintf (dump_file,
		  	   "Edge %i->%i is inconsistent, count"HOST_WIDEST_INT_PRINT_DEC,
			   e->src->index, e->dest->index, e->count);
		  dump_bb (dump_file, e->src, 0, TDF_DETAILS);
		  dump_bb (dump_file, e->dest, 0, TDF_DETAILS);
		}
              return true;
	    }
        }
    }
  return false;
}
