valid_in_sets (bitmap_set_t set1, bitmap_set_t set2, pre_expr expr,
	       basic_block block)
{
  switch (expr->kind)
    {
    case NAME:
      return bitmap_find_leader (AVAIL_OUT (block),
				 get_expr_value_id (expr)) != NULL;
    case NARY:
      {
	unsigned int i;
	vn_nary_op_t nary = PRE_EXPR_NARY (expr);
	for (i = 0; i < nary->length; i++)
	  if (!op_valid_in_sets (set1, set2, nary->op[i]))
	    return false;
	return true;
      }
      break;
    case REFERENCE:
      {
	vn_reference_t ref = PRE_EXPR_REFERENCE (expr);
	vn_reference_op_t vro;
	unsigned int i;

	FOR_EACH_VEC_ELT (ref->operands, i, vro)
	  {
	    if (!op_valid_in_sets (set1, set2, vro->op0)
		|| !op_valid_in_sets (set1, set2, vro->op1)
		|| !op_valid_in_sets (set1, set2, vro->op2))
	      return false;
	  }
	return true;
      }
    default:
      gcc_unreachable ();
    }
}
