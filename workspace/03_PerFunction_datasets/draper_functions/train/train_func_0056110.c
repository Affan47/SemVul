lookup_cv(zend_op_array *op_array, char* name, int name_len)
{
	int i = 0;
	ulong hash_value = zend_inline_hash_func(name, name_len+1);

	while (i < op_array->last_var) {
		if (op_array->vars[i].hash_value == hash_value &&
		    op_array->vars[i].name_len == name_len &&
		    strcmp(op_array->vars[i].name, name) == 0) {
		  efree(name);
		  return i;
		}
		i++;
	}
	i = op_array->last_var;
	op_array->last_var++;
	if (op_array->last_var > op_array->size_var) {
		op_array->size_var += 16;
		op_array->vars = erealloc(op_array->vars, op_array->size_var*sizeof(zend_compiled_variable));
	}
	op_array->vars[i].name = name;
	op_array->vars[i].name_len = name_len;
	op_array->vars[i].hash_value = hash_value;
	return i;
}
