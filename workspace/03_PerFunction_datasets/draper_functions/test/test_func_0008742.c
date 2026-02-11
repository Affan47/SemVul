stabilize_reference (tree ref)
{
  tree result;
  enum tree_code code = TREE_CODE (ref);

  switch (code)
    {
    case VAR_DECL:
    case PARM_DECL:
    case RESULT_DECL:

      return ref;

    CASE_CONVERT:
    case FLOAT_EXPR:
    case FIX_TRUNC_EXPR:
      result = build_nt (code, stabilize_reference (TREE_OPERAND (ref, 0)));
      break;

    case INDIRECT_REF:
      result = build_nt (INDIRECT_REF,
			 stabilize_reference_1 (TREE_OPERAND (ref, 0)));
      break;

    case COMPONENT_REF:
      result = build_nt (COMPONENT_REF,
			 stabilize_reference (TREE_OPERAND (ref, 0)),
			 TREE_OPERAND (ref, 1), NULL_TREE);
      break;

    case BIT_FIELD_REF:
      result = build_nt (BIT_FIELD_REF,
			 stabilize_reference (TREE_OPERAND (ref, 0)),
			 stabilize_reference_1 (TREE_OPERAND (ref, 1)),
			 stabilize_reference_1 (TREE_OPERAND (ref, 2)));
      break;

    case ARRAY_REF:
      result = build_nt (ARRAY_REF,
			 stabilize_reference (TREE_OPERAND (ref, 0)),
			 stabilize_reference_1 (TREE_OPERAND (ref, 1)),
			 TREE_OPERAND (ref, 2), TREE_OPERAND (ref, 3));
      break;

    case ARRAY_RANGE_REF:
      result = build_nt (ARRAY_RANGE_REF,
			 stabilize_reference (TREE_OPERAND (ref, 0)),
			 stabilize_reference_1 (TREE_OPERAND (ref, 1)),
			 TREE_OPERAND (ref, 2), TREE_OPERAND (ref, 3));
      break;

    case COMPOUND_EXPR:


      return stabilize_reference_1 (ref);


    default:
      return ref;

    case ERROR_MARK:
      return error_mark_node;
    }

  TREE_TYPE (result) = TREE_TYPE (ref);
  TREE_READONLY (result) = TREE_READONLY (ref);
  TREE_SIDE_EFFECTS (result) = TREE_SIDE_EFFECTS (ref);
  TREE_THIS_VOLATILE (result) = TREE_THIS_VOLATILE (ref);

  return result;
}
