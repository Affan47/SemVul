build_ref_from_constant_pool (int index)
{
  tree i;
  tree d = TYPE_CPOOL_DATA_REF (output_class);

  if (d == NULL_TREE)
    d = build_constant_data_ref (flag_indirect_classes);

  i = build_int_cst (NULL_TREE, index);
  d = build4 (ARRAY_REF, TREE_TYPE (TREE_TYPE (d)), d, i,
		 NULL_TREE, NULL_TREE);
  return d;
}
