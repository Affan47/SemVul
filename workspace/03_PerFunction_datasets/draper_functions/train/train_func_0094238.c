array_size_for_constructor (tree val)
{
  tree max_index, i;


  if (TREE_CODE (val) == STRING_CST)
    return TREE_STRING_LENGTH (val);

  max_index = NULL_TREE;
  for (i = CONSTRUCTOR_ELTS (val); i; i = TREE_CHAIN (i))
    {
      tree index = TREE_PURPOSE (i);

      if (TREE_CODE (index) == RANGE_EXPR)
	index = TREE_OPERAND (index, 1);
      if (max_index == NULL_TREE || tree_int_cst_lt (max_index, index))
	max_index = index;
    }

  if (max_index == NULL_TREE)
    return 0;


  i = size_binop (MINUS_EXPR, convert (sizetype, max_index),
		  convert (sizetype,
			   TYPE_MIN_VALUE (TYPE_DOMAIN (TREE_TYPE (val)))));
  i = size_binop (PLUS_EXPR, i, convert (sizetype, integer_one_node));


  i = size_binop (MULT_EXPR, i, TYPE_SIZE_UNIT (TREE_TYPE (TREE_TYPE (val))));

  return tree_low_cst (i, 1);
}
