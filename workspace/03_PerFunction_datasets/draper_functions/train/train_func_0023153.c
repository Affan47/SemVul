acpi_print_osc_error(acpi_handle handle,
	struct acpi_osc_context *context, char *error)
{
	struct acpi_buffer buffer = {ACPI_ALLOCATE_BUFFER};
	int i;

	if (ACPI_FAILURE(acpi_get_name(handle, ACPI_FULL_PATHNAME, &buffer)))
		printk(KERN_DEBUG "%s\n", error);
	else {
		printk(KERN_DEBUG "%s:%s\n", (char *)buffer.pointer, error);
		kfree(buffer.pointer);
	}
	printk(KERN_DEBUG"_OSC request data:");
	for (i = 0; i < context->cap.length; i += sizeof(u32))
		printk("%x ", *((u32 *)(context->cap.pointer + i)));
	printk("\n");
}
