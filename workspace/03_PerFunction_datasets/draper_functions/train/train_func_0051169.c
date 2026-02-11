visit(ir_dereference_variable *ir)
{
   variable_entry *entry = this->get_variable_entry(ir->var);


   if (entry)
      entry->split = false;

   return visit_continue;
}
