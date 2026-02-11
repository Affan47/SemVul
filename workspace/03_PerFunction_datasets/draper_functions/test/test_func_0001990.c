vm_jni_lookup_method(const char *class_name, const char *method_name,
			   const char *method_type)
{
	char *mangled_class_name;
	char *mangled_method_name;
	char *mangled_method_type;
	char *symbol_name;
	void *sym_addr;
	char *method_args;

	method_args = get_method_args(method_type);

	mangled_class_name = vm_jni_get_mangled_name(class_name);
	mangled_method_name = vm_jni_get_mangled_name(method_name);
	mangled_method_type = vm_jni_get_mangled_name(method_args);

	symbol_name = NULL;
	if (asprintf(&symbol_name, "Java_%s_%s__%s", mangled_class_name,
		 mangled_method_name, mangled_method_type) < 0)
		die("asprintf");

	sym_addr = vm_jni_lookup_symbol(symbol_name);
	if (sym_addr)
		goto out;

	if (asprintf(&symbol_name, "Java_%s_%s", mangled_class_name,
		 mangled_method_name) < 0)
		die("asprintf");

	sym_addr = vm_jni_lookup_symbol(symbol_name);

 out:
	free(method_args);
	free(mangled_method_name);
	free(mangled_class_name);
	free(mangled_method_type);
	free(symbol_name);

	return sym_addr;
}
