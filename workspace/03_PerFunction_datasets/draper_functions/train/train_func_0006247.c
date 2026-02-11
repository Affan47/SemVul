lookup_destructor (tree object, tree scope, tree dtor_name)
{
  tree object_type = TREE_TYPE (object);
  tree dtor_type = TREE_OPERAND (dtor_name, 0);
  tree expr;

  if (scope && !check_dtor_name (scope, dtor_name))
    {
      error ("qualified type `%T' does not match destructor name `~%T'",
	     scope, dtor_type);
      return error_mark_node;
    }
  if (!DERIVED_FROM_P (dtor_type, TYPE_MAIN_VARIANT (object_type)))
    {
      error ("the type being destroyed is `%T', but the destructor refers to `%T'",
	     TYPE_MAIN_VARIANT (object_type), dtor_type);
      return error_mark_node;
    }
  if (!TYPE_HAS_DESTRUCTOR (dtor_type))
    return build (PSEUDO_DTOR_EXPR, void_type_node, object, scope,
		  dtor_type);
  expr = lookup_member (dtor_type, complete_dtor_identifier,
			1, false);
  expr = (adjust_result_of_qualified_name_lookup
	  (expr, dtor_type, object_type));
  return expr;
}
