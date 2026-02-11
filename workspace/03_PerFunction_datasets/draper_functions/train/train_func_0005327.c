visit_leave(ir_assignment *ir)
{


   ir_rvalue_visitor::visit_leave(ir);

   if (this->is_clip_distance_vec8(ir->lhs) ||
       this->is_clip_distance_vec8(ir->rhs)) {


      void *ctx = ralloc_parent(ir);
      int array_size = ir->lhs->type->array_size();
      for (int i = 0; i < array_size; ++i) {
         ir_dereference_array *new_lhs = new(ctx) ir_dereference_array(
            ir->lhs->clone(ctx, NULL), new(ctx) ir_constant(i));
         ir_dereference_array *new_rhs = new(ctx) ir_dereference_array(
            ir->rhs->clone(ctx, NULL), new(ctx) ir_constant(i));
         this->handle_rvalue((ir_rvalue **) &new_rhs);


         ir_assignment *const assign = new(ctx) ir_assignment(new_lhs, new_rhs);
         this->handle_rvalue((ir_rvalue **) &assign->lhs);
         this->fix_lhs(assign);

         this->base_ir->insert_before(assign);
      }
      ir->remove();

      return visit_continue;
   }


   handle_rvalue((ir_rvalue **)&ir->lhs);
   this->fix_lhs(ir);

   return rvalue_visit(ir);
}
