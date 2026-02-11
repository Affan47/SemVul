java_lang_VMClass_getDeclaredClasses(jobject klass, jboolean public_only)
{
	struct vm_object *result;
	unsigned int count = 0;
	unsigned int index = 0;
	struct vm_class *vmc;

	vmc = vm_object_to_vm_class(klass);
	if (!vmc)
		return NULL;

	for (unsigned int i = 0; i < vmc->nr_inner_classes; i++) {
		uint16_t inner_ndx = vmc->inner_classes[i];
		struct vm_class *inner_vmc;

		inner_vmc = vm_class_resolve_class(vmc, inner_ndx);
		if (!inner_vmc)
			return rethrow_exception();

		if (!vm_class_is_public(inner_vmc) && public_only)
			continue;

		count++;
	}

	result = vm_object_alloc_array(vm_array_of_java_lang_Class, count);
	if (!result)
		return rethrow_exception();

	for (unsigned int i = 0; i < vmc->nr_inner_classes; i++) {
		uint16_t inner_ndx = vmc->inner_classes[i];
		struct vm_class *inner_vmc;

		inner_vmc = vm_class_resolve_class(vmc, inner_ndx);
		if (!inner_vmc)
			return rethrow_exception();

		if (!vm_class_is_public(inner_vmc) && public_only)
			continue;

		array_set_field_ptr(result, index++, inner_vmc->object);
	}

	return result;
}
