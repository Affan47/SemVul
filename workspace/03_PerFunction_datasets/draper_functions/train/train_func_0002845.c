intel_pstate_no_acpi_pss(void)
{
	int i;

	for_each_possible_cpu(i) {
		acpi_status status;
		union acpi_object *pss;
		struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
		struct acpi_processor *pr = per_cpu(processors, i);

		if (!pr)
			continue;

		status = acpi_evaluate_object(pr->handle, "_PSS", NULL, &buffer);
		if (ACPI_FAILURE(status))
			continue;

		pss = buffer.pointer;
		if (pss && pss->type == ACPI_TYPE_PACKAGE) {
			kfree(pss);
			return false;
		}

		kfree(pss);
	}

	return true;
}
