acpi_parse_art(acpi_handle handle, int *art_count, struct art **artp,
		bool create_dev)
{
	acpi_status status;
	int result = 0;
	int i;
	int nr_bad_entries = 0;
	struct art *arts;
	struct acpi_device *adev;
	union acpi_object *p;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	struct acpi_buffer element = { 0, NULL };
	struct acpi_buffer art_format =	{
		sizeof("RRNNNNNNNNNNN"), "RRNNNNNNNNNNN" };

	if (!acpi_has_method(handle, "_ART"))
		return -ENODEV;

	status = acpi_evaluate_object(handle, "_ART", NULL, &buffer);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	p = buffer.pointer;
	if (!p || (p->type != ACPI_TYPE_PACKAGE)) {
		pr_err("Invalid _ART data\n");
		result = -EFAULT;
		goto end;
	}


	*art_count = p->package.count - 1;
	arts = kzalloc(*art_count * sizeof(struct art), GFP_KERNEL);
	if (!arts) {
		result = -ENOMEM;
		goto end;
	}

	for (i = 0; i < *art_count; i++) {
		struct art *art = &arts[i - nr_bad_entries];

		element.length = sizeof(struct art);
		element.pointer = art;

		status = acpi_extract_package(&(p->package.elements[i + 1]),
					      &art_format, &element);
		if (ACPI_FAILURE(status)) {
			pr_warn("_ART package %d is invalid, ignored", i);
			nr_bad_entries++;
			continue;
		}
		if (!create_dev)
			continue;

		if (art->source) {
			result = acpi_bus_get_device(art->source, &adev);
			if (result)
				pr_warn("Failed to get source ACPI device\n");
		}
		if (art->target) {
			result = acpi_bus_get_device(art->target, &adev);
			if (result)
				pr_warn("Failed to get source ACPI device\n");
		}
	}

	*artp = arts;

	*art_count -= nr_bad_entries;
end:
	kfree(buffer.pointer);
	return result;
}
