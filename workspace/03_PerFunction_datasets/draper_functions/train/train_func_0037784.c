swizzle_if_required(ir_expression *expr,
					  ir_rvalue *operand)
{
   if (expr->type->is_vector() && operand->type->is_scalar()) {
      return new(mem_ctx) ir_swizzle(operand, 0, 0, 0, 0,
				     expr->type->vector_elements);
   } else
      return operand;
}
