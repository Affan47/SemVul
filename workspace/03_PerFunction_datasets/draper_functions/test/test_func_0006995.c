field_get_value(struct vm_field *vmf, struct vm_object *o)
{
	void *value_p;


	if (vm_field_is_static(vmf)) {
		value_p = vmf->class->static_values + vmf->offset;
	} else {


		if (!o) {
			signal_new_exception(vm_java_lang_NullPointerException, NULL);
			return NULL;
		}

		if (!vm_object_is_instance_of(o, vmf->class)) {
			signal_new_exception(vm_java_lang_IllegalArgumentException, NULL);
			return NULL;
		}

		value_p = field_get_object_ptr(o, vmf->offset);
	}

	return value_p;
}
