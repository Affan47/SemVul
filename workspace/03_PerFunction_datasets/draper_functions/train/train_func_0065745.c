store_init_value (tree decl, tree init)
{
  tree value, type;


  type = TREE_TYPE (decl);
  if (TREE_CODE (type) == ERROR_MARK)
    return NULL_TREE;

  if (IS_AGGR_TYPE (type))
    {
      if (! TYPE_HAS_TRIVIAL_INIT_REF (type)
	  && TREE_CODE (init) != CONSTRUCTOR)
	abort ();

      if (TREE_CODE (init) == TREE_LIST)
	{
	  error ("constructor syntax used, but no constructor declared for type `%T'", type);
	  init = build_constructor (NULL_TREE, nreverse (init));
	}
    }
  else if (TREE_CODE (init) == TREE_LIST
	   && TREE_TYPE (init) != unknown_type_node)
    {
      if (TREE_CODE (decl) == RESULT_DECL)
	init = build_x_compound_expr_from_list (init,
						"return value initializer");
      else if (TREE_CODE (init) == TREE_LIST
	       && TREE_CODE (TREE_TYPE (decl)) == ARRAY_TYPE)
	{
	  error ("cannot initialize arrays using this syntax");
	  return NULL_TREE;
	}
      else

	init = build_x_compound_expr_from_list (init, "initializer");
    }


  value = digest_init (type, init, (tree *) 0);


  if (value != error_mark_node
      && (! TREE_CONSTANT (value)
	  || ! initializer_constant_valid_p (value, TREE_TYPE (value))))
    return split_nonconstant_init (decl, value);


  DECL_INITIAL (decl) = value;
  return NULL_TREE;
}
