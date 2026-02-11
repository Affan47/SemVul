do_dead_code(exec_list *instructions, bool uniform_locations_assigned)
{
   ir_variable_refcount_visitor v;
   bool progress = false;

   v.run(instructions);

   struct hash_entry *e;
   hash_table_foreach(v.ht, e) {
      ir_variable_refcount_entry *entry = (ir_variable_refcount_entry *)e->data;


      assert(entry->referenced_count >= entry->assigned_count);

      if (debug) {
	 printf("%s@%p: %d refs, %d assigns, %sdeclared in our scope\n",
		entry->var->name, (void *) entry->var,
		entry->referenced_count, entry->assigned_count,
		entry->declaration ? "" : "not ");
      }

      if ((entry->referenced_count > entry->assigned_count)
	  || !entry->declaration)
	 continue;

      if (entry->assign) {


	 if (entry->var->data.mode != ir_var_function_out &&
	     entry->var->data.mode != ir_var_function_inout &&
             entry->var->data.mode != ir_var_shader_out) {
	    entry->assign->remove();
	    progress = true;

	    if (debug) {
	       printf("Removed assignment to %s@%p\n",
		      entry->var->name, (void *) entry->var);
	    }
	 }
      } else {


	 if (entry->var->data.mode == ir_var_uniform &&
	     (uniform_locations_assigned ||
	      entry->var->constant_value))
	    continue;

	 entry->var->remove();
	 progress = true;

	 if (debug) {
	    printf("Removed declaration of %s@%p\n",
		   entry->var->name, (void *) entry->var);
	 }
      }
   }

   return progress;
}
