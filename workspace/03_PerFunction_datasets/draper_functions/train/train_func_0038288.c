get_reaching_def (tree var)
{
  tree currdef;


  currdef = get_current_def (var);


  if (currdef == NULL_TREE)
    {
      tree sym = DECL_P (var) ? var : SSA_NAME_VAR (var);
      currdef = get_default_def_for (sym);
      set_current_def (var, currdef);
    }


  return currdef;
}
