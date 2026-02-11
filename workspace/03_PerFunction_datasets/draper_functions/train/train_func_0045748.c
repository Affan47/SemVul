rvalue_visit(ir_expression *ir)
{
   unsigned int operand;

   for (operand = 0; operand < ir->get_num_operands(); operand++) {
      handle_rvalue(&ir->operands[operand]);
   }

   return visit_continue;
}
