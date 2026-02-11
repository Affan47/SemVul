do_structure_splitting(exec_list *instructions)
{
   ir_structure_reference_visitor refs;

   visit_list_elements(&refs, instructions);


   foreach_list_safe(n, &refs.variable_list) {
      variable_entry *entry = (variable_entry *) n;

      if (debug) {
	 printf("structure %s@%p: decl %d, whole_access %d\n",
		entry->var->name, (void *) entry->var, entry->declaration,
		entry->whole_structure_access);
      }

      if (!entry->declaration || entry->whole_structure_access) {
	 entry->remove();
      }
   }

   if (refs.variable_list.is_empty())
      return false;

   void *mem_ctx = ralloc_context(NULL);


   foreach_list_safe(n, &refs.variable_list) {
      variable_entry *entry = (variable_entry *) n;
      const struct glsl_type *type = entry->var->type;

      entry->mem_ctx = ralloc_parent(entry->var);

      entry->components = ralloc_array(mem_ctx,
				       ir_variable *,
				       type->length);

      for (unsigned int i = 0; i < entry->var->type->length; i++) {
	 const char *name = ralloc_asprintf(mem_ctx, "%s_%s",
					    entry->var->name,
					    type->fields.structure[i].name);

	 entry->components[i] =
	    new(entry->mem_ctx) ir_variable(type->fields.structure[i].type,
					    name,
					    ir_var_temporary);
	 entry->var->insert_before(entry->components[i]);
      }

      entry->var->remove();
   }

   ir_structure_splitting_visitor split(&refs.variable_list);
   visit_list_elements(&split, instructions);

   ralloc_free(mem_ctx);

   return true;
}
