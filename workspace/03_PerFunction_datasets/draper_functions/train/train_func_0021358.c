dup_vars(struct ast_variable *v)
{
	struct ast_variable *new, *list = NULL;
	for (; v; v = v->next) {
		if (!(new = ast_variable_new(v->name, v->value, v->file))) {
			ast_variables_destroy(list);
			return NULL;
		}


		new->next = list;
		list = new;
	}
	return list;
}
