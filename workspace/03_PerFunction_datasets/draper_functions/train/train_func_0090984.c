vm_preload_add_class_fixup(struct vm_class *vmc)
{
	int new_size = sizeof(struct vm_class *) * (nr_class_fixups + 1);
	struct vm_class **new_array = realloc(class_fixups, new_size);

	if (!new_array)
		return -ENOMEM;

	class_fixups = new_array;
	class_fixups[nr_class_fixups++] = vmc;
	return 0;
}
