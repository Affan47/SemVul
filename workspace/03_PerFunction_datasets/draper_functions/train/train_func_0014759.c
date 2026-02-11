create_new_def_for (tree old_name, gimple stmt, def_operand_p def)
{
  tree new_name = duplicate_ssa_name (old_name, stmt);

  SET_DEF (def, new_name);

  if (gimple_code (stmt) == GIMPLE_PHI)
    {
      basic_block bb = gimple_bb (stmt);


      SSA_NAME_OCCURS_IN_ABNORMAL_PHI (new_name) = bb_has_abnormal_pred (bb);
    }

  register_new_name_mapping (new_name, old_name);


  set_current_def (old_name, new_name);

  return new_name;
}
