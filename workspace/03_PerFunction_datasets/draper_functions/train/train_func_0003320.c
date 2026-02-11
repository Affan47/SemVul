complex_unroll(ir_loop *ir, int iterations,
                                    bool continue_from_then_branch)
{
   void *const mem_ctx = ralloc_parent(ir);
   ir_instruction *ir_to_replace = ir;

   for (int i = 0; i < iterations; i++) {
      exec_list copy_list;

      copy_list.make_empty();
      clone_ir_list(mem_ctx, &copy_list, &ir->body_instructions);

      ir_if *ir_if = ((ir_instruction *) copy_list.get_tail())->as_if();
      assert(ir_if != NULL);

      ir_to_replace->insert_before(&copy_list);
      ir_to_replace->remove();


      ir_to_replace =
         new(mem_ctx) ir_loop_jump(ir_loop_jump::jump_continue);

      exec_list *const list = (continue_from_then_branch)
         ? &ir_if->then_instructions : &ir_if->else_instructions;

      list->push_tail(ir_to_replace);
   }

   ir_to_replace->remove();

   this->progress = true;
}
