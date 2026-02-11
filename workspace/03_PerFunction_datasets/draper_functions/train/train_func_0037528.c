lto_input_ts_decl_non_common_tree_pointers (struct lto_input_block *ib,
					    struct data_in *data_in, tree expr)
{
  if (TREE_CODE (expr) == FUNCTION_DECL)
    {
      DECL_ARGUMENTS (expr) = lto_input_tree (ib, data_in);
      DECL_RESULT (expr) = lto_input_tree (ib, data_in);
    }
  DECL_VINDEX (expr) = lto_input_tree (ib, data_in);
}
