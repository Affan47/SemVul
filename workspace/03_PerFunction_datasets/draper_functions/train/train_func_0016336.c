free_all_edge_infos (void)
{
  basic_block bb;
  edge_iterator ei;
  edge e;

  FOR_EACH_BB (bb)
    {
      FOR_EACH_EDGE (e, ei, bb->preds)
        {
	 struct edge_info *edge_info = (struct edge_info *) e->aux;

	  if (edge_info)
	    {
	      edge_info->cond_equivalences.release ();
	      free (edge_info);
	      e->aux = NULL;
	    }
	}
    }
}
