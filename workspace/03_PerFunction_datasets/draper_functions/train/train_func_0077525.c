lto_input_ts_decl_common_tree_pointers (struct lto_input_block *ib,
					struct data_in *data_in, tree expr)
{
  DECL_SIZE (expr) = stream_read_tree (ib, data_in);
  DECL_SIZE_UNIT (expr) = stream_read_tree (ib, data_in);
  DECL_ATTRIBUTES (expr) = stream_read_tree (ib, data_in);


  if (TREE_CODE (expr) == PARM_DECL)
    TREE_CHAIN (expr) = streamer_read_chain (ib, data_in);

  if ((TREE_CODE (expr) == VAR_DECL
       || TREE_CODE (expr) == PARM_DECL)
      && DECL_HAS_VALUE_EXPR_P (expr))
    SET_DECL_VALUE_EXPR (expr, stream_read_tree (ib, data_in));

  if (TREE_CODE (expr) == VAR_DECL)
    {
      tree dexpr = stream_read_tree (ib, data_in);
      if (dexpr)
	SET_DECL_DEBUG_EXPR (expr, dexpr);
    }
}
