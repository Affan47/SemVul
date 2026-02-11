native_constructor_get_modifiers_internal(struct vm_object *ctor)
{
	struct vm_object *clazz;
	struct vm_class *class;
	struct vm_method *vmm;
	int slot;

	if (!ctor) {
		signal_new_exception(vm_java_lang_NullPointerException, NULL);
		return 0;
	}

	if (vm_java_lang_reflect_VMConstructor != NULL) {
		clazz	= field_get_object(ctor, vm_java_lang_reflect_VMConstructor_clazz);
		slot	= field_get_int(ctor, vm_java_lang_reflect_VMConstructor_slot);
	} else {
		clazz = field_get_object(ctor, vm_java_lang_reflect_Constructor_clazz);
		slot = field_get_int(ctor, vm_java_lang_reflect_Constructor_slot);
	}

	class = vm_class_get_class_from_class_object(clazz);
	vmm = &class->methods[slot];

	return vmm->method->access_flags;
}
