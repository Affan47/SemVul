ccp_visit_stmt (gimple stmt, edge *taken_edge_p, tree *output_p)
{
  tree def;
  ssa_op_iter iter;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "\nVisiting statement:\n");
      print_gimple_stmt (dump_file, stmt, 0, dump_flags);
    }

  switch (gimple_code (stmt))
    {
      case GIMPLE_ASSIGN:


        return visit_assignment (stmt, output_p);

      case GIMPLE_CALL:

        if (gimple_call_lhs (stmt) != NULL_TREE)
          return visit_assignment (stmt, output_p);
        break;

      case GIMPLE_COND:
      case GIMPLE_SWITCH:


        return visit_cond_stmt (stmt, taken_edge_p);

      default:
        break;
    }


  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "No interesting values produced.  Marked VARYING.\n");


  FOR_EACH_SSA_TREE_OPERAND (def, stmt, iter, SSA_OP_ALL_DEFS)
    {
      prop_value_t v = { VARYING, NULL_TREE, { -1, (HOST_WIDE_INT) -1 } };
      set_lattice_value (def, v);
    }

  return SSA_PROP_VARYING;
}
