dynv_var_color_set(struct dynvVariable* variable, void* value, bool deref){
	if (!variable->ptr_value) return -1;
	memcpy(variable->ptr_value, *(void**)value, sizeof(float[4]));


	return 0;
}
