append_internal_var_def_use_entry(Statement *dest_statement,
				  Var_table *new_var_table,
				  Def_use   def_or_use)
{
    Def_use_table *new = NULL;
    Def_use_table *current = NULL;

    switch (def_or_use) {
      case DEF:
	current = dest_statement->def_var_list;
	break;
      case USE:
	current = dest_statement->use_var_list;
	break;
      default:

	break;
    }

    for ( ; current->next != NULL; current = current->next) {
	;
    }
    if ((new = (Def_use_table *)
	 calloc(1, sizeof(Def_use_table))) == NULL) {
	fatal("No more room for Def_use_table.\n");
    }
    new->table = new_var_table->kind;
    new->entry = new_var_table->entry;
    new->sub_id_ptr = NULL;
    new->prev = current;
    current->next = new;
    new->next = NULL;
}
