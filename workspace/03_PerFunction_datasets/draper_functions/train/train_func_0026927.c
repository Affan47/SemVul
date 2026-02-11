fully_constant_vn_reference_p (vn_reference_t ref)
{
  vec<vn_reference_op_s> operands = ref->operands;
  vn_reference_op_t op;


  op = &operands[0];
  if (op->opcode == CALL_EXPR
      && TREE_CODE (op->op0) == ADDR_EXPR
      && TREE_CODE (TREE_OPERAND (op->op0, 0)) == FUNCTION_DECL
      && DECL_BUILT_IN (TREE_OPERAND (op->op0, 0))
      && operands.length () >= 2
      && operands.length () <= 3)
    {
      vn_reference_op_t arg0, arg1 = NULL;
      bool anyconst = false;
      arg0 = &operands[1];
      if (operands.length () > 2)
	arg1 = &operands[2];
      if (TREE_CODE_CLASS (arg0->opcode) == tcc_constant
	  || (arg0->opcode == ADDR_EXPR
	      && is_gimple_min_invariant (arg0->op0)))
	anyconst = true;
      if (arg1
	  && (TREE_CODE_CLASS (arg1->opcode) == tcc_constant
	      || (arg1->opcode == ADDR_EXPR
		  && is_gimple_min_invariant (arg1->op0))))
	anyconst = true;
      if (anyconst)
	{
	  tree folded = build_call_expr (TREE_OPERAND (op->op0, 0),
					 arg1 ? 2 : 1,
					 arg0->op0,
					 arg1 ? arg1->op0 : NULL);
	  if (folded
	      && TREE_CODE (folded) == NOP_EXPR)
	    folded = TREE_OPERAND (folded, 0);
	  if (folded
	      && is_gimple_min_invariant (folded))
	    return folded;
	}
    }


  else if (op->opcode == ARRAY_REF
	   && TREE_CODE (op->op0) == INTEGER_CST
	   && integer_zerop (op->op1)
	   && operands.length () == 2)
    {
      vn_reference_op_t arg0;
      arg0 = &operands[1];
      if (arg0->opcode == STRING_CST
	  && (TYPE_MODE (op->type)
	      == TYPE_MODE (TREE_TYPE (TREE_TYPE (arg0->op0))))
	  && GET_MODE_CLASS (TYPE_MODE (op->type)) == MODE_INT
	  && GET_MODE_SIZE (TYPE_MODE (op->type)) == 1
	  && tree_int_cst_sgn (op->op0) >= 0
	  && compare_tree_int (op->op0, TREE_STRING_LENGTH (arg0->op0)) < 0)
	return build_int_cst_type (op->type,
				   (TREE_STRING_POINTER (arg0->op0)
				    [TREE_INT_CST_LOW (op->op0)]));
    }

  return NULL_TREE;
}
