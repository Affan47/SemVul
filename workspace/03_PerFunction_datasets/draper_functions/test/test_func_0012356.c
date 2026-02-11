java_lang_VMClass_forName(struct vm_object *name, jboolean initialize, struct vm_object *loader)
{
	struct vm_class *class;
	char *class_name;

	if (!name) {
		signal_new_exception(vm_java_lang_NullPointerException, NULL);
		return NULL;
	}

	class_name = vm_string_to_cstr(name);
	if (!class_name)
		return throw_oom_error();

	class = classloader_load(loader, class_name);
	if (!class)
		goto throw_cnf;

	if (initialize) {
		if (vm_class_ensure_init(class))
			goto throw_cnf;
	}

	return class->object;
 throw_cnf:
	signal_new_exception(vm_java_lang_ClassNotFoundException, class_name);
	free(class_name);
	return NULL;
}
