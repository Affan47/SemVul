create_nesting_tree (struct cgraph_node *cgn)
{
  struct nesting_info *info = XCNEW (struct nesting_info);
  info->field_map = pointer_map_create ();
  info->var_map = pointer_map_create ();
  info->mem_refs = pointer_set_create ();
  info->suppress_expansion = BITMAP_ALLOC (&nesting_info_bitmap_obstack);
  info->context = cgn->symbol.decl;

  for (cgn = cgn->nested; cgn ; cgn = cgn->next_nested)
    {
      struct nesting_info *sub = create_nesting_tree (cgn);
      sub->outer = info;
      sub->next = info->inner;
      info->inner = sub;
    }


  if (check_for_nested_with_variably_modified (info->context, info->context))
    DECL_UNINLINABLE (info->context) = true;

  return info;
}
