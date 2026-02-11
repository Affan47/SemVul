kill(ir_variable *var, unsigned write_mask)
{
   assert(var != NULL);


   if (!var->type->is_vector() && !var->type->is_scalar())
      return;


   foreach_iter(exec_list_iterator, iter, *this->acp) {
      acp_entry *entry = (acp_entry *)iter.get();

      if (entry->var == var) {
	 entry->write_mask &= ~write_mask;
	 if (entry->write_mask == 0)
	    entry->remove();
      }
   }


   foreach_iter(exec_list_iterator, iter, *this->kills) {
      kill_entry *entry = (kill_entry *)iter.get();

      if (entry->var == var) {
	 entry->write_mask |= write_mask;
	 return;
      }
   }

   this->kills->push_tail(new(this->mem_ctx) kill_entry(var, write_mask));
}
