set_current_def (tree var, tree def)
{
  if (TREE_CODE (var) == SSA_NAME)
    get_ssa_name_ann (var)->current_def = def;
  else
    var_ann (var)->current_def = def;
}
