visit(ir_if *ir)
{
   if (ir->condition->type != glsl_type::bool_type) {
      printf("ir_if condition %s type instead of bool.\n",
	     ir->condition->type->name);
      ir->print();
      printf("\n");
      abort();
   }

   return visit_continue;
}
