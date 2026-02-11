replace_discard(void *mem_ctx, ir_variable *var, ir_discard *ir)
{
   ir_rvalue *condition = ir->condition;


   if (condition == NULL)
      condition = new(mem_ctx) ir_constant(true);

   ir_assignment *assignment =
      new(mem_ctx) ir_assignment(new(mem_ctx) ir_dereference_variable(var),
				 condition, NULL);

   ir->replace_with(assignment);
}
