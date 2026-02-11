process_replaceable (temp_expr_table_p tab, gimple stmt, int call_cnt)
{
  tree var, def, basevar;
  int version;
  ssa_op_iter iter;
  bitmap def_vars, use_vars;

  gcc_checking_assert (is_replaceable_p (stmt, true));

  def = SINGLE_SSA_TREE_OPERAND (stmt, SSA_OP_DEF);
  version = SSA_NAME_VERSION (def);
  def_vars = BITMAP_ALLOC (&ter_bitmap_obstack);

  basevar = SSA_NAME_VAR (def);
  if (basevar)
    bitmap_set_bit (def_vars, DECL_UID (basevar));


  FOR_EACH_SSA_TREE_OPERAND (var, stmt, iter, SSA_OP_USE)
    {
      int var_version = SSA_NAME_VERSION (var);

      use_vars = tab->expr_decl_uids[var_version];
      add_dependence (tab, version, var);
      if (use_vars)
        {
	  bitmap_ior_into (def_vars, use_vars);
	  BITMAP_FREE (tab->expr_decl_uids[var_version]);
	}
      else if (SSA_NAME_VAR (var))
	bitmap_set_bit (def_vars, DECL_UID (SSA_NAME_VAR (var)));
    }
  tab->expr_decl_uids[version] = def_vars;


  if (gimple_vuse (stmt))
    {
      make_dependent_on_partition (tab, version, VIRTUAL_PARTITION (tab));
      add_to_partition_kill_list (tab, VIRTUAL_PARTITION (tab), version);
    }

  tab->call_cnt[version] = call_cnt;
}
