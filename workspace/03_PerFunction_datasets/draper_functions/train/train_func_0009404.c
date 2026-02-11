check_node_type(ir_instruction *ir, void *data)
{
   (void) data;

   if (ir->ir_type <= ir_type_unset || ir->ir_type >= ir_type_max) {
      printf("Instruction node with unset type\n");
      ir->print(); printf("\n");
   }
   ir_rvalue *value = ir->as_rvalue();
   if (value != NULL)
      assert(value->type != glsl_type::error_type);
}
