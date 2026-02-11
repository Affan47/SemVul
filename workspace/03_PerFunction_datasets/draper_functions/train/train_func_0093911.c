vect_get_vec_defs (tree op0, tree op1, gimple stmt,
		   vec<tree> *vec_oprnds0,
		   vec<tree> *vec_oprnds1,
		   slp_tree slp_node, int reduc_index)
{
  if (slp_node)
    {
      int nops = (op1 == NULL_TREE) ? 1 : 2;
      vec<tree> ops;
      ops.create (nops);
      vec<vec<tree> > vec_defs;
      vec_defs.create (nops);

      ops.quick_push (op0);
      if (op1)
        ops.quick_push (op1);

      vect_get_slp_defs (ops, slp_node, &vec_defs, reduc_index);

      *vec_oprnds0 = vec_defs[0];
      if (op1)
	*vec_oprnds1 = vec_defs[1];

      ops.release ();
      vec_defs.release ();
    }
  else
    {
      tree vec_oprnd;

      vec_oprnds0->create (1);
      vec_oprnd = vect_get_vec_def_for_operand (op0, stmt, NULL);
      vec_oprnds0->quick_push (vec_oprnd);

      if (op1)
	{
	  vec_oprnds1->create (1);
	  vec_oprnd = vect_get_vec_def_for_operand (op1, stmt, NULL);
	  vec_oprnds1->quick_push (vec_oprnd);
	}
    }
}
