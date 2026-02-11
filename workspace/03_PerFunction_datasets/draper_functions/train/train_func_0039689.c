lookup_method(struct vm_class *class, const char *method_name)
{
	int i;

	for (i = 0; i < class->nr_ptrs; i++) {
		struct vm_method *method = class->method_ptrs + i;

		if (!strcmp(method->method_name, method_name))
			return method->method_ptr;
	}

	return NULL;
}
