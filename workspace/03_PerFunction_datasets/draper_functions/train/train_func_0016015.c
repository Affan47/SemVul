visit(ir_dereference_variable *ir)
{
   ir_variable *var = ir->var;

   if (!var->is_in_uniform_block())
      return visit_continue;

   assert(!var->is_interface_instance() || !var->type->is_array());


   link_uniform_block_active *const b =
      process_block(this->mem_ctx, this->ht, var);
   if (b == NULL) {
      linker_error(this->prog,
		   "uniform block `%s' has mismatching definitions",
		   var->get_interface_type()->name);
      this->success = false;
      return visit_stop;
   }

   assert(b->num_array_elements == 0);
   assert(b->array_elements == NULL);
   assert(b->type != NULL);

   return visit_continue;
}
