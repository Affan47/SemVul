insert_native(struct vm_class *class, const char *method_name, void *ptr)
{
	struct vm_method *method;
	unsigned long new_size;

	class->nr_ptrs++;
	new_size = class->nr_ptrs * sizeof(struct vm_method);
	class->method_ptrs = realloc(class->method_ptrs, new_size);
	if (!class->method_ptrs)
		return -ENOMEM;

	method = class->method_ptrs + class->nr_ptrs-1;
	method->method_name = method_name;
	method->method_ptr  = ptr;;

	return 0;
}
