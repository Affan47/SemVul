replace_return_with_assignment(ir_instruction *ir, void *data)
{
   void *ctx = ralloc_parent(ir);
   ir_dereference *orig_deref = (ir_dereference *) data;
   ir_return *ret = ir->as_return();

   if (ret) {
      if (ret->value) {
	 ir_rvalue *lhs = orig_deref->clone(ctx, NULL);
	 ret->replace_with(new(ctx) ir_assignment(lhs, ret->value, NULL));
      } else {


	 assert(ret->next->is_tail_sentinel());
	 ret->remove();
      }
   }
}
