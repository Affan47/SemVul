as_rvalue_to_saturate()
{
   ir_expression *expr = this->as_expression();

   if (!expr)
      return NULL;

   ir_rvalue *max_zero = try_max_zero(expr);
   if (max_zero) {
      return try_min_one(max_zero);
   } else {
      ir_rvalue *min_one = try_min_one(expr);
      if (min_one) {
	 return try_max_zero(min_one);
      }
   }

   return NULL;
}
