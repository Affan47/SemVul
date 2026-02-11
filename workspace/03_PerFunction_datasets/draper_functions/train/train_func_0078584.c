visit_enter(ir_function *ir)
{


   if (this->current_function != NULL) {
      printf("Function definition nested inside another function "
	     "definition:\n");
      printf("%s %p inside %s %p\n",
	     ir->name, (void *) ir,
	     this->current_function->name, (void *) this->current_function);
      abort();
   }


   this->current_function = ir;

   this->validate_ir(ir, this->data);


   foreach_list(node, &ir->signatures) {
      ir_instruction *sig = (ir_instruction *) node;

      if (sig->ir_type != ir_type_function_signature) {
	 printf("Non-signature in signature list of function `%s'\n",
		ir->name);
	 abort();
      }
   }

   return visit_continue;
}
