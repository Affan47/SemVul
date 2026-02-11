expand_unordered_cmp (function, params, unordered_code, ordered_code)
     tree function, params;
     enum tree_code unordered_code, ordered_code;
{
  tree arg0, arg1, type;
  enum tree_code code0, code1;


  if (params == 0 || TREE_CHAIN (params) == 0)
    {
      error ("too few arguments to function `%s'",
	     IDENTIFIER_POINTER (DECL_NAME (function)));
      return error_mark_node;
    }
  else if (TREE_CHAIN (TREE_CHAIN (params)) != 0)
    {
      error ("too many arguments to function `%s'",
	     IDENTIFIER_POINTER (DECL_NAME (function)));
      return error_mark_node;
    }

  arg0 = TREE_VALUE (params);
  arg1 = TREE_VALUE (TREE_CHAIN (params));

  code0 = TREE_CODE (TREE_TYPE (arg0));
  code1 = TREE_CODE (TREE_TYPE (arg1));


  type = 0;
  if ((code0 == INTEGER_TYPE || code0 == REAL_TYPE)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE))
    type = common_type (TREE_TYPE (arg0), TREE_TYPE (arg1));

  if (type == 0 || TREE_CODE (type) != REAL_TYPE)
    {
      error ("non-floating-point argument to function `%s'",
	     IDENTIFIER_POINTER (DECL_NAME (function)));
      return error_mark_node;
    }

  if (unordered_code == UNORDERED_EXPR)
    {
      if (MODE_HAS_NANS (TYPE_MODE (type)))
	return build_binary_op (unordered_code,
				convert (type, arg0),
				convert (type, arg1),
				0);
      else
	return integer_zero_node;
    }

  return build_unary_op (TRUTH_NOT_EXPR,
			 build_binary_op (MODE_HAS_NANS (TYPE_MODE (type))
					  ? unordered_code
					  : ordered_code,
					  convert (type, arg0),
					  convert (type, arg1),
					  0),
			 0);
}
