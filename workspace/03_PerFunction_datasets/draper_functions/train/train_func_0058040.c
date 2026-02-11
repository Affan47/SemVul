visit(ir_dereference_variable *ir)
{
   ir_variable *const var = ir->var;
   variable_entry *entry = this->get_variable_entry(var);

   if (entry)
      entry->whole_vector_access++;

   return visit_continue;
}
