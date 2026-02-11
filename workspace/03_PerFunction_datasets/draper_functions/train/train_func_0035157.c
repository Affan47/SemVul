output_used_types_helper (void **slot, void *data)
{
  tree type = (tree) *slot;
  VEC(tree, heap) **types_p = (VEC(tree, heap) **) data;

  if ((TREE_CODE (type) == RECORD_TYPE
       || TREE_CODE (type) == UNION_TYPE
       || TREE_CODE (type) == QUAL_UNION_TYPE
       || TREE_CODE (type) == ENUMERAL_TYPE)
      && TYPE_STUB_DECL (type)
      && DECL_P (TYPE_STUB_DECL (type))
      && ! DECL_IGNORED_P (TYPE_STUB_DECL (type)))
    VEC_quick_push (tree, *types_p, TYPE_STUB_DECL (type));
  else if (TYPE_NAME (type)
	   && TREE_CODE (TYPE_NAME (type)) == TYPE_DECL)
    VEC_quick_push (tree, *types_p, TYPE_NAME (type));

  return 1;
}
