lookup_qualified_name (tree scope, tree name, bool is_type_p, bool complain)
{
  int flags = 0;

  if (TREE_CODE (scope) == NAMESPACE_DECL)
    {
      cxx_binding binding;

      cxx_binding_clear (&binding);
      flags |= LOOKUP_COMPLAIN;
      if (is_type_p)
	flags |= LOOKUP_PREFER_TYPES;
      if (qualified_lookup_using_namespace (name, scope, &binding, flags))
	return select_decl (&binding, flags);
    }
  else if (is_aggr_type (scope, complain))
    {
      tree t;
      t = lookup_member (scope, name, 0, is_type_p);
      if (t)
	return t;
    }

  return error_mark_node;
}
