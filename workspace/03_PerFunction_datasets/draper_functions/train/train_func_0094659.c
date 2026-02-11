read_instructions(exec_list *instructions, s_expression *expr,
			     ir_loop *loop_ctx)
{

   s_list *list = SX_AS_LIST(expr);
   if (list == NULL) {
      ir_read_error(expr, "Expected (<instruction> ...); found an atom.");
      return;
   }

   foreach_list(n, &list->subexpressions) {
      s_expression *sub = (s_expression *) n;
      ir_instruction *ir = read_instruction(sub, loop_ctx);
      if (ir != NULL) {


	 if (state->current_function == NULL && ir->as_variable() != NULL)
	    instructions->push_head(ir);
	 else
	    instructions->push_tail(ir);
      }
   }
}
