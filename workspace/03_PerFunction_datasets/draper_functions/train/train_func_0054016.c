known_alignment (tree exp)
{
  unsigned int this_alignment;
  unsigned int lhs, rhs;

  switch (TREE_CODE (exp))
    {
    CASE_CONVERT:
    case VIEW_CONVERT_EXPR:
    case NON_LVALUE_EXPR:


      this_alignment = known_alignment (TREE_OPERAND (exp, 0));
      break;

    case COMPOUND_EXPR:

      this_alignment = known_alignment (TREE_OPERAND (exp, 1));
      break;

    case PLUS_EXPR:
    case MINUS_EXPR:


      lhs = known_alignment (TREE_OPERAND (exp, 0));
      rhs = known_alignment (TREE_OPERAND (exp, 1));
      this_alignment = MIN (lhs, rhs);
      break;

    case POINTER_PLUS_EXPR:
      lhs = known_alignment (TREE_OPERAND (exp, 0));
      rhs = known_alignment (TREE_OPERAND (exp, 1));


      if (rhs == 0)
	this_alignment = lhs;
      else
	this_alignment = MIN (lhs, rhs);
      break;

    case COND_EXPR:

      lhs = known_alignment (TREE_OPERAND (exp, 1));
      rhs = known_alignment (TREE_OPERAND (exp, 2));
      this_alignment = MIN (lhs, rhs);
      break;

    case INTEGER_CST:
      {
	unsigned HOST_WIDE_INT c = TREE_INT_CST_LOW (exp);


	this_alignment = MIN (BITS_PER_UNIT * (c & -c), BIGGEST_ALIGNMENT);
      }
      break;

    case MULT_EXPR:


      lhs = known_alignment (TREE_OPERAND (exp, 0));
      rhs = known_alignment (TREE_OPERAND (exp, 1));

      if (lhs == 0)
	this_alignment = rhs;
      else if (rhs == 0)
	this_alignment = lhs;
      else
	this_alignment = MIN (lhs * rhs, BIGGEST_ALIGNMENT);
      break;

    case BIT_AND_EXPR:


      this_alignment = known_alignment (TREE_OPERAND (exp, 1));
      break;

    case ADDR_EXPR:
      this_alignment = expr_align (TREE_OPERAND (exp, 0));
      break;

    case CALL_EXPR:
      {
	tree t = maybe_inline_call_in_expr (exp);
	if (t)
	  return known_alignment (t);
      }


    default:


      if (POINTER_TYPE_P (TREE_TYPE (exp))
	  && !TYPE_IS_DUMMY_P (TREE_TYPE (TREE_TYPE (exp))))
	this_alignment = TYPE_ALIGN (TREE_TYPE (TREE_TYPE (exp)));
      else
	this_alignment = 0;
      break;
    }

  return this_alignment;
}
