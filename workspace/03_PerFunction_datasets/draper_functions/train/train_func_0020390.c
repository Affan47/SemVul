get_types_needing_access_check (tree t)
{
  tree ti;
  VEC(qualified_typedef_usage_t,gc) *result = NULL;

  if (!t || t == error_mark_node)
    return NULL;

  if (!(ti = get_template_info (t)))
    return NULL;

  if (CLASS_TYPE_P (t)
      || TREE_CODE (t) == FUNCTION_DECL)
    {
      if (!TI_TEMPLATE (ti))
	return NULL;

      result = TI_TYPEDEFS_NEEDING_ACCESS_CHECKING (ti);
    }

  return result;
}
