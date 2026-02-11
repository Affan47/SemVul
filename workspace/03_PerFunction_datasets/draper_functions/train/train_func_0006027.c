copy_var_table(Var_table *var_head, Common_table *head)
{
    Var_table *ret = NULL;

    if (var_head) {
	ret = alloc_var_table();
	ret->entry = var_head->entry;
	ret->type = var_head->type;
	ret->next = var_head->next;
    if (var_head->name != NULL) {
        ret->name = copy_name(var_head->name);
    } else {
        ret->name = create_new_name(ret->entry, KIND_VAR);
    }
	ret->size = var_head->size;
        ret->save = var_head->save;

	ret->node =
	  fit_link_var_or_array_and_node(var_head->node, head);
	ret->kind = var_head->kind;

        ret->type_entry = var_head->type_entry;
	ret->is_global = var_head->is_global;
	ret->import_flg = var_head->import_flg;
    ret->static_flg = var_head->static_flg;
    ret->const_flg = var_head->const_flg;
    ret->volatile_flg = var_head->volatile_flg;
    ret->restrict_flg = ret->restrict_flg;
	ret->rank = var_head->rank;
	ret->members = var_head->members;
	ret->structure = var_head->structure;
    }
    return(ret);
}
