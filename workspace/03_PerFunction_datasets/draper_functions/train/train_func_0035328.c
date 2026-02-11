mark_def_sites (basic_block bb, gimple stmt, bitmap kills)
{
  tree def;
  use_operand_p use_p;
  ssa_op_iter iter;


  update_stmt (stmt);

  gcc_checking_assert (blocks_to_update == NULL);
  set_register_defs (stmt, false);
  set_rewrite_uses (stmt, false);

  if (is_gimple_debug (stmt))
    {
      FOR_EACH_SSA_USE_OPERAND (use_p, stmt, iter, SSA_OP_USE)
	{
	  tree sym = USE_FROM_PTR (use_p);
	  gcc_checking_assert (DECL_P (sym));
	  set_rewrite_uses (stmt, true);
	}
      if (rewrite_uses_p (stmt))
	bitmap_set_bit (interesting_blocks, bb->index);
      return;
    }


  FOR_EACH_SSA_USE_OPERAND (use_p, stmt, iter, SSA_OP_ALL_USES)
    {
      tree sym = USE_FROM_PTR (use_p);
      gcc_checking_assert (DECL_P (sym));
      if (!bitmap_bit_p (kills, DECL_UID (sym)))
	set_livein_block (sym, bb);
      set_rewrite_uses (stmt, true);
    }


  FOR_EACH_SSA_TREE_OPERAND (def, stmt, iter, SSA_OP_ALL_DEFS)
    {
      gcc_checking_assert (DECL_P (def));
      set_def_block (def, bb, false);
      bitmap_set_bit (kills, DECL_UID (def));
      set_register_defs (stmt, true);
    }


  if (rewrite_uses_p (stmt) || register_defs_p (stmt))
    bitmap_set_bit (interesting_blocks, bb->index);
}
