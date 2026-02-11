extract_package(struct acpi_battery *battery,
			   union acpi_object *package,
			   const struct acpi_offsets *offsets, int num)
{
	int i;
	union acpi_object *element;
	if (package->type != ACPI_TYPE_PACKAGE)
		return -EFAULT;
	for (i = 0; i < num; ++i) {
		if (package->package.count <= i)
			return -EFAULT;
		element = &package->package.elements[i];
		if (offsets[i].mode) {
			u8 *ptr = (u8 *)battery + offsets[i].offset;
			if (element->type == ACPI_TYPE_STRING ||
			    element->type == ACPI_TYPE_BUFFER)
				strncpy(ptr, element->string.pointer, 32);
			else if (element->type == ACPI_TYPE_INTEGER) {
				strncpy(ptr, (u8 *)&element->integer.value,
					sizeof(u64));
				ptr[sizeof(u64)] = 0;
			} else
				*ptr = 0;
		} else {
			int *x = (int *)((u8 *)battery + offsets[i].offset);
			*x = (element->type == ACPI_TYPE_INTEGER) ?
				element->integer.value : -1;
		}
	}
	return 0;
}
