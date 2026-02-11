steal_memory(ir_instruction *ir, void *new_ctx)
{
   ir_variable *var = ir->as_variable();
   ir_constant *constant = ir->as_constant();
   if (var != NULL && var->constant_value != NULL)
      steal_memory(var->constant_value, ir);


   if (constant != NULL) {
      if (constant->type->is_record()) {
	 foreach_iter(exec_list_iterator, iter, constant->components) {
	    ir_constant *field = (ir_constant *)iter.get();
	    steal_memory(field, ir);
	 }
      } else if (constant->type->is_array()) {
	 for (unsigned int i = 0; i < constant->type->length; i++) {
	    steal_memory(constant->array_elements[i], ir);
	 }
      }
   }

   ralloc_steal(new_ctx, ir);
}
