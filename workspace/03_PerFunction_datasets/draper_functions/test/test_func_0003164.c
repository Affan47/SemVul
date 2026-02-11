dotlike(operand a, operand b)
{
   assert(a.val->type == b.val->type);

   if (a.val->type->vector_elements == 1)
      return expr(ir_binop_mul, a, b);

   return expr(ir_binop_dot, a, b);
}
