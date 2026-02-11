add_copy(ir_assignment *ir)
{
   acp_entry *entry;
   int orig_swizzle[4] = {0, 1, 2, 3};
   int swizzle[4];

   if (ir->condition)
      return;

   ir_dereference_variable *lhs = ir->lhs->as_dereference_variable();
   if (!lhs || !(lhs->type->is_scalar() || lhs->type->is_vector()))
      return;

   ir_dereference_variable *rhs = ir->rhs->as_dereference_variable();
   if (!rhs) {
      ir_swizzle *swiz = ir->rhs->as_swizzle();
      if (!swiz)
	 return;

      rhs = swiz->val->as_dereference_variable();
      if (!rhs)
	 return;

      orig_swizzle[0] = swiz->mask.x;
      orig_swizzle[1] = swiz->mask.y;
      orig_swizzle[2] = swiz->mask.z;
      orig_swizzle[3] = swiz->mask.w;
   }


   int j = 0;
   for (int i = 0; i < 4; i++) {
      if (ir->write_mask & (1 << i))
	 swizzle[i] = orig_swizzle[j++];
   }

   if (lhs->var->precision != rhs->var->precision && lhs->var->precision!=glsl_precision_undefined && rhs->var->precision!=glsl_precision_undefined)
      return;

   entry = new(this->mem_ctx) acp_entry(lhs->var, rhs->var, ir->write_mask,
					swizzle);
   this->acp->push_tail(entry);
}
