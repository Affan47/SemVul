get_assignment_entry(ir_variable *var, exec_list *list)
{
   struct assignment_entry *entry;

   foreach_list_typed(struct assignment_entry, entry, link, list) {
      if (entry->var == var)
	 return entry;
   }

   entry = (struct assignment_entry *)calloc(1, sizeof(*entry));
   entry->var = var;
   list->push_head(&entry->link);
   return entry;
}
