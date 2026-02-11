dynv_var_string_get(struct dynvVariable* variable, void** value, bool *deref){
	if (variable->ptr_value){
		*value = &variable->ptr_value;
		return 0;
	}
	return -1;
}
