build_prim_array_type (tree element_type, HOST_WIDE_INT length)
{
  tree index = NULL;

  if (length != -1)
    {
      tree max_index = build_int_cst (sizetype, length - 1);
      index = build_index_type (max_index);
    }
  return build_array_type (element_type, index);
}
