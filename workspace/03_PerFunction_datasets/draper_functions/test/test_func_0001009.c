vm_class_implements(const struct vm_class *vmc, const struct vm_class *from)
{
	for (unsigned int i = 0; i < from->nr_interfaces; ++i) {
		if (vmc == from->interfaces[i] || vm_class_implements(vmc, from->interfaces[i]))
			return true;
	}

	if (from->super)
		return vm_class_implements(vmc, from->super);

	return false;
}
