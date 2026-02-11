visit_leave(ir_if *ir)
{

   if (ir->then_instructions.is_empty() &&
       ir->else_instructions.is_empty()) {
      ir->remove();
      this->made_progress = true;
      return visit_continue;
   }


   ir_constant *condition_constant = ir->condition->constant_expression_value();
   if (condition_constant) {


      if (condition_constant->value.b[0]) {
	 foreach_list_safe(n, &ir->then_instructions) {
	    ir_instruction *then_ir = (ir_instruction *) n;
	    ir->insert_before(then_ir);
	 }
      } else {
	 foreach_list_safe(n, &ir->else_instructions) {
	    ir_instruction *else_ir = (ir_instruction *) n;
	    ir->insert_before(else_ir);
	 }
      }
      ir->remove();
      this->made_progress = true;
      return visit_continue;
   }


   if (ir->then_instructions.is_empty()) {
      ir->condition = new(ralloc_parent(ir->condition))
	 ir_expression(ir_unop_logic_not, ir->condition);
      ir->else_instructions.move_nodes_to(&ir->then_instructions);
      this->made_progress = true;
   }

   return visit_continue;
}
