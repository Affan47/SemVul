is_arg_in_array_table(Module_table *module, Array_table *array)
{
    Operand *arg;

    for (arg = module->arg_head; arg != NULL; arg = arg->next) {
	if (arg->kind == KIND_ARRAY) {
	    if (arg->entry == array->entry) {
		return TRUE;
	    }
	}
    }
    return FALSE;
}
