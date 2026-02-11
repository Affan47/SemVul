build_exception_handlers_table(struct compilation_unit *cu)
{
	struct vm_method *method;
	int size;
	int i;

	method = cu->method;
	size = method->code_attribute.exception_table_length;

	if (size == 0)
		return 0;

	cu->exception_handlers = malloc(sizeof(void *) * size);
	if (!cu->exception_handlers)
		return -ENOMEM;

	for (i = 0; i < size; i++) {
		struct cafebabe_code_attribute_exception *eh
			= &method->code_attribute.exception_table[i];

		cu->exception_handlers[i] = eh_native_ptr(cu, eh);
	}

	return 0;
}
