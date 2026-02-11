rename_variables_for_op(Operand* op, Module_table* mptr,
			const int* correspond_array, int var_num)
{
    Var_table*  new_var;

    for (; op != NULL; op = op->next) {
	if (op->kind == KIND_VAR
	    && op->entry < var_num && correspond_array[op->entry] > 0) {
	    new_var = search_var_table(mptr->var_head,
				       correspond_array[op->entry]);

	    op->entry = new_var->entry;
	    op->tbl.v = new_var;
	}

	rename_variables_for_op(op->inner, mptr, correspond_array, var_num);
    }
}
