calc_dfs_tree_nonrec (struct dom_info *di, basic_block bb, enum cdi_direction reverse)
{


  edge e;
  TBB child_i, my_i = 0;
  edge *stack;
  int sp;


  basic_block en_block;

  basic_block ex_block;

  stack = xmalloc ((n_basic_blocks + 3) * sizeof (edge));
  sp = 0;


  if (reverse)
    {
      e = bb->pred;
      en_block = EXIT_BLOCK_PTR;
      ex_block = ENTRY_BLOCK_PTR;
    }
  else
    {
      e = bb->succ;
      en_block = ENTRY_BLOCK_PTR;
      ex_block = EXIT_BLOCK_PTR;
    }


  while (1)
    {
      basic_block bn;


      while (e)
	{
	  edge e_next;


	  if (reverse)
	    {
	      bn = e->src;


	      if (bn == ex_block || di->dfs_order[bn->index])
		{
		  e = e->pred_next;
		  continue;
		}
	      bb = e->dest;
	      e_next = bn->pred;
	    }
	  else
	    {
	      bn = e->dest;
	      if (bn == ex_block || di->dfs_order[bn->index])
		{
		  e = e->succ_next;
		  continue;
		}
	      bb = e->src;
	      e_next = bn->succ;
	    }

	  if (bn == en_block)
	    abort ();


	  if (bb != en_block)
	    my_i = di->dfs_order[bb->index];
	  else
	    my_i = di->dfs_order[last_basic_block];
	  child_i = di->dfs_order[bn->index] = di->dfsnum++;
	  di->dfs_to_bb[child_i] = bn;
	  di->dfs_parent[child_i] = my_i;


	  stack[sp++] = e;
	  e = e_next;
	}

      if (!sp)
	break;
      e = stack[--sp];


      if (reverse)
	e = e->pred_next;
      else
	e = e->succ_next;
    }
  free (stack);
}
