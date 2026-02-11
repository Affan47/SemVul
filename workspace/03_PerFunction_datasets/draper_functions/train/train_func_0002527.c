visit_leave(ir_if *ir)
{


   if (ir->then_instructions.is_empty() || !ir->else_instructions.is_empty())
      return visit_continue;

   ir_if *inner = ((ir_instruction *) ir->then_instructions.head)->as_if();
   if (!inner || !inner->next->is_tail_sentinel() ||
       !inner->else_instructions.is_empty())
      return visit_continue;

   ir->condition = logic_and(ir->condition, inner->condition);
   inner->then_instructions.move_nodes_to(&ir->then_instructions);

   progress = true;
   return visit_continue;
}
