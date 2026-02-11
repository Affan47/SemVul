fix_parameter(void *mem_ctx, ir_rvalue *actual, const glsl_type *formal_type,
              exec_list *before_instructions, exec_list *after_instructions,
              bool parameter_is_inout)
{
   ir_expression *const expr = actual->as_expression();


   if (formal_type == actual->type
       && (expr == NULL || expr->operation != ir_binop_vector_extract))
      return;


   ir_variable *tmp =
      new(mem_ctx) ir_variable(formal_type, "inout_tmp", ir_var_temporary);

   before_instructions->push_tail(tmp);


   if (parameter_is_inout) {


      assert (actual->type == formal_type);

      ir_dereference_variable *const deref_tmp_1 =
         new(mem_ctx) ir_dereference_variable(tmp);
      ir_assignment *const assignment =
         new(mem_ctx) ir_assignment(deref_tmp_1, actual);
      before_instructions->push_tail(assignment);
   }


   ir_dereference_variable *const deref_tmp_2 =
      new(mem_ctx) ir_dereference_variable(tmp);
   actual->replace_with(deref_tmp_2);


   ir_rvalue *rhs = new(mem_ctx) ir_dereference_variable(tmp);
   if (actual->type != formal_type)
      rhs = convert_component(rhs, actual->type);

   ir_rvalue *lhs = actual;
   if (expr != NULL && expr->operation == ir_binop_vector_extract) {
      rhs = new(mem_ctx) ir_expression(ir_triop_vector_insert,
                                       expr->operands[0]->type,
                                       expr->operands[0]->clone(mem_ctx, NULL),
                                       rhs,
                                       expr->operands[1]->clone(mem_ctx, NULL));
      lhs = expr->operands[0]->clone(mem_ctx, NULL);
   }

   ir_assignment *const assignment_2 = new(mem_ctx) ir_assignment(lhs, rhs);
   after_instructions->push_tail(assignment_2);
}
