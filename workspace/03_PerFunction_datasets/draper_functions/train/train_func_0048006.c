lto_input_ts_type_non_common_tree_pointers (struct lto_input_block *ib,
					    struct data_in *data_in,
					    tree expr)
{
  if (TREE_CODE (expr) == ENUMERAL_TYPE)
    TYPE_VALUES (expr) = stream_read_tree (ib, data_in);
  else if (TREE_CODE (expr) == ARRAY_TYPE)
    TYPE_DOMAIN (expr) = stream_read_tree (ib, data_in);
  else if (RECORD_OR_UNION_TYPE_P (expr))
    TYPE_FIELDS (expr) = streamer_read_chain (ib, data_in);
  else if (TREE_CODE (expr) == FUNCTION_TYPE
	   || TREE_CODE (expr) == METHOD_TYPE)
    TYPE_ARG_TYPES (expr) = stream_read_tree (ib, data_in);

  if (!POINTER_TYPE_P (expr))
    TYPE_MINVAL (expr) = stream_read_tree (ib, data_in);
  TYPE_MAXVAL (expr) = stream_read_tree (ib, data_in);
  if (RECORD_OR_UNION_TYPE_P (expr))
    TYPE_BINFO (expr) = stream_read_tree (ib, data_in);
}
