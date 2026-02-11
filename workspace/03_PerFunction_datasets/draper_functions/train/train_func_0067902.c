lookup_cv(zend_op_array *op_array, char* name, int name_len, ulong hash TSRMLS_DC)
{
	int i = 0;
	ulong hash_value = hash ? hash : zend_inline_hash_func(name, name_len+1);

	while (i < op_array->last_var) {
		if (op_array->vars[i].name == name ||
		    (op_array->vars[i].hash_value == hash_value &&
		     op_array->vars[i].name_len == name_len &&
		     memcmp(op_array->vars[i].name, name, name_len) == 0)) {
			str_efree(name);
			return i;
		}
		i++;
	}
	i = op_array->last_var;
	op_array->last_var++;
	if (op_array->last_var > CG(context).vars_size) {
		CG(context).vars_size += 16;
		op_array->vars = erealloc(op_array->vars, CG(context).vars_size * sizeof(zend_compiled_variable));
	}
	op_array->vars[i].name = zend_new_interned_string(name, name_len + 1, 1 TSRMLS_CC);
	op_array->vars[i].name_len = name_len;
	op_array->vars[i].hash_value = hash_value;
	return i;
}
