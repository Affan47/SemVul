strip_invariant_refs (const_tree op)
{
  while (handled_component_p (op))
    {
      switch (TREE_CODE (op))
	{
	case ARRAY_REF:
	case ARRAY_RANGE_REF:
	  if (!is_gimple_constant (TREE_OPERAND (op, 1))
	      || TREE_OPERAND (op, 2) != NULL_TREE
	      || TREE_OPERAND (op, 3) != NULL_TREE)
	    return NULL;
	  break;

	case COMPONENT_REF:
	  if (TREE_OPERAND (op, 2) != NULL_TREE)
	    return NULL;
	  break;

	default:;
	}
      op = TREE_OPERAND (op, 0);
    }

  return op;
}
