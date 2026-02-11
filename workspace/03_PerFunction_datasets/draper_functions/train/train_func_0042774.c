verify_ssa_name (tree ssa_name, bool is_virtual)
{
  if (TREE_CODE (ssa_name) != SSA_NAME)
    {
      error ("expected an SSA_NAME object");
      return true;
    }

  if (TREE_TYPE (ssa_name) != TREE_TYPE (SSA_NAME_VAR (ssa_name)))
    {
      error ("type mismatch between an SSA_NAME and its symbol");
      return true;
    }

  if (SSA_NAME_IN_FREE_LIST (ssa_name))
    {
      error ("found an SSA_NAME that had been released into the free pool");
      return true;
    }

  if (is_virtual && is_gimple_reg (ssa_name))
    {
      error ("found a virtual definition for a GIMPLE register");
      return true;
    }

  if (is_virtual && SSA_NAME_VAR (ssa_name) != gimple_vop (cfun))
    {
      error ("virtual SSA name for non-VOP decl");
      return true;
    }

  if (!is_virtual && !is_gimple_reg (ssa_name))
    {
      error ("found a real definition for a non-register");
      return true;
    }

  if (SSA_NAME_IS_DEFAULT_DEF (ssa_name)
      && !gimple_nop_p (SSA_NAME_DEF_STMT (ssa_name)))
    {
      error ("found a default name with a non-empty defining statement");
      return true;
    }

  return false;
}
