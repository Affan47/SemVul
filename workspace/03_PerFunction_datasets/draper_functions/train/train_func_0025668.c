tsubst_template_parms (tree parms, tree args, tsubst_flags_t complain)
{
  tree r = NULL_TREE;
  tree* new_parms;


  ++processing_template_decl;

  for (new_parms = &r;
       parms && TMPL_PARMS_DEPTH (parms) > TMPL_ARGS_DEPTH (args);
       new_parms = &(TREE_CHAIN (*new_parms)),
	 parms = TREE_CHAIN (parms))
    {
      tree new_vec =
	make_tree_vec (TREE_VEC_LENGTH (TREE_VALUE (parms)));
      int i;

      for (i = 0; i < TREE_VEC_LENGTH (new_vec); ++i)
	{
          tree tuple;

          if (parms == error_mark_node)
            continue;

          tuple = TREE_VEC_ELT (TREE_VALUE (parms), i);

          if (tuple == error_mark_node)
            continue;

	  TREE_VEC_ELT (new_vec, i) =
	    tsubst_template_parm (tuple, args, complain);
	}

      *new_parms =
	tree_cons (size_int (TMPL_PARMS_DEPTH (parms)
			     - TMPL_ARGS_DEPTH (args)),
		   new_vec, NULL_TREE);
    }

  --processing_template_decl;

  return r;
}
