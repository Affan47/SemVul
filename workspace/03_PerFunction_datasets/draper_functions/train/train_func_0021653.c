is_bitfield_expr_with_lowered_type (const_tree exp)
{
  switch (TREE_CODE (exp))
    {
    case COND_EXPR:
      if (!is_bitfield_expr_with_lowered_type (TREE_OPERAND (exp, 1)
					       ? TREE_OPERAND (exp, 1)
					       : TREE_OPERAND (exp, 0)))
	return NULL_TREE;
      return is_bitfield_expr_with_lowered_type (TREE_OPERAND (exp, 2));

    case COMPOUND_EXPR:
      return is_bitfield_expr_with_lowered_type (TREE_OPERAND (exp, 1));

    case MODIFY_EXPR:
    case SAVE_EXPR:
      return is_bitfield_expr_with_lowered_type (TREE_OPERAND (exp, 0));

    case COMPONENT_REF:
      {
	tree field;

	field = TREE_OPERAND (exp, 1);
	if (TREE_CODE (field) != FIELD_DECL || !DECL_BIT_FIELD_TYPE (field))
	  return NULL_TREE;
	if (same_type_ignoring_top_level_qualifiers_p
	    (TREE_TYPE (exp), DECL_BIT_FIELD_TYPE (field)))
	  return NULL_TREE;
	return DECL_BIT_FIELD_TYPE (field);
      }

    CASE_CONVERT:
      if (TYPE_MAIN_VARIANT (TREE_TYPE (TREE_OPERAND (exp, 0)))
	  == TYPE_MAIN_VARIANT (TREE_TYPE (exp)))
	return is_bitfield_expr_with_lowered_type (TREE_OPERAND (exp, 0));


    default:
      return NULL_TREE;
    }
}
