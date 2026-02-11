visit_enter(ir_assignment *ir)
{
   ir->rhs->accept(this);
   handle_rvalue(&ir->rhs);

   if (ir->condition) {
      ir->condition->accept(this);
      handle_rvalue(&ir->condition);

      ir_constant *const_val = ir->condition->as_constant();


      if (const_val) {
	 if (const_val->value.b[0])
	    ir->condition = NULL;
	 else
	    ir->remove();
	 this->progress = true;
      }
   }


   return visit_continue_with_parent;
}
