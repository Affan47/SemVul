make_rename_temp (tree type, const char *prefix)
{
  tree t = create_tmp_reg (type, prefix);

  if (gimple_referenced_vars (cfun))
    {
      add_referenced_var (t);
      mark_sym_for_renaming (t);
    }

  return t;
}
