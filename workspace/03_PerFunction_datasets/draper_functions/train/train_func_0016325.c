vm_class_get_method(const struct vm_class *vmc,
	const char *name, const char *type)
{
	if (vmc->kind != VM_CLASS_KIND_REGULAR)
		return NULL;

	for (unsigned int i = 0; i < vmc->nr_methods; ++i) {
		struct vm_method *vmm = &vmc->methods[i];

		if (!strcmp(vmm->name, name) && !strcmp(vmm->type, type))
			return vmm;
	}

	return NULL;
}
