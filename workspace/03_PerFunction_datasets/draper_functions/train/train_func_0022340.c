setup_vtable(struct vm_class *vmc)
{
	struct vm_class *super;
	unsigned int super_vtable_size;
	struct vtable *super_vtable;
	unsigned int vtable_size;

	super = vmc->super;

	if (super) {
		super_vtable_size = super->vtable_size;
		super_vtable = &super->vtable;
	} else {
		super_vtable_size = 0;
	}

	vtable_size = 0;
	for (uint16_t i = 0; i < vmc->nr_methods; ++i) {
		struct vm_method *vmm = &vmc->methods[i];

		if (super) {
			struct vm_method *vmm2
				= vm_class_get_method_recursive(super,
					vmm->name, vmm->type);
			if (vmm2) {
				vmm->virtual_index = vmm2->virtual_index;
				continue;
			}
		}

		vmm->virtual_index = super_vtable_size + vtable_size;
		++vtable_size;
	}

	vmc->vtable_size = super_vtable_size + vtable_size;

	vtable_init(&vmc->vtable, vmc->vtable_size);


	for (uint16_t i = 0; i < super_vtable_size; ++i)
		vtable_setup_method(&vmc->vtable, i,
			super_vtable->native_ptr[i]);


	for (uint16_t i = 0; i < vmc->nr_methods; ++i) {
		struct vm_method *vmm = &vmc->methods[i];

		vtable_setup_method(&vmc->vtable,
				    vmm->virtual_index,
				    vm_method_call_ptr(vmm));
	}
}
