move_block_to_cond_assign(void *mem_ctx,
			  ir_if *if_ir, ir_rvalue *cond_expr,
			  exec_list *instructions,
			  struct hash_table *ht)
{
   foreach_list_safe(node, instructions) {
      ir_instruction *ir = (ir_instruction *) node;

      if (ir->ir_type == ir_type_assignment) {
	 ir_assignment *assign = (ir_assignment *)ir;

	 if (hash_table_find(ht, assign) == NULL) {
	    hash_table_insert(ht, assign, assign);


	    const bool assign_to_cv =
	       hash_table_find(ht, assign->lhs->variable_referenced()) != NULL;

	    if (!assign->condition) {
	       if (assign_to_cv) {
		  assign->rhs =
		     new(mem_ctx) ir_expression(ir_binop_logic_and,
						glsl_type::bool_type,
						cond_expr->clone(mem_ctx, NULL),
						assign->rhs);
	       } else {
		  assign->condition = cond_expr->clone(mem_ctx, NULL);
	       }
	    } else {
	       assign->condition =
		  new(mem_ctx) ir_expression(ir_binop_logic_and,
					     glsl_type::bool_type,
					     cond_expr->clone(mem_ctx, NULL),
					     assign->condition);
	    }
	 }
      }


      ir->remove();
      if_ir->insert_before(ir);
   }
}
